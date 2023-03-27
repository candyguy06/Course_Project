`include "timescale.v"
// synopsys translate_on


module interrupt_controller(irq,rst_n,clk,if_pc,mem_pc,intctl_epc,intctl_status,intctl_cause,iack,id2intctl_status);			
			input [5:0]	irq;
			// Interrupt Request 中斷類型 : 發生哪種中斷
			input 	rst_n;
			input 	clk;
			input 	if_pc;
			input	mem_pc;
			// program counter 程式計數器 紀錄程式下一個要執行位置
			input	[31:0] id2intctl_status;
			// id2 processor status and control
			output 	[31:0] intctl_epc;
			// processor status and control
			output 	[31:0] intctl_cause;
			// cause of last general exception
			output 	[31:0] intctl_status;
			// program counter at last exception
			output  iack;
			// interrupt acknowledge : 告訴external device，processor是否正在處理中斷的訊號
			reg   	[31:0]	intctl_epc;
			reg   	[31:0]	intctl_cause;
			reg		[31:0]	intctl_status;

			wire    [31:0]	if_pc;
			wire    [31:0]	mem_pc;
			reg				iack;
			
		
		always@(negedge clk or negedge rst_n)
		// clk and rst_n 負元觸發
        begin	
			if(~rst_n)
				// reset 歸0
					begin
					iack<=1'b0;
					// assign0給iack
					intctl_epc <= 32'd0;
					// assign32bit的0給intctl_epc		
					intctl_status<=	32'd0;	
					// assign32bit的0給intctl_status				
					intctl_cause <= 32'd0;
					// assign32bit的0給intctl_cause	
					end
			else if( ((irq[5]&id2intctl_status[15])|(irq[4]&id2intctl_status[14])|(irq[3]&id2intctl_status[13])
					|(irq[2]&id2intctl_status[12])|(irq[1]&id2intctl_status[11])|(irq[0]&id2intctl_status[10])) & id2intctl_status[0] )
				// IPL(IM7~IM2) : Interrupt Mask: Control the enabling of each of the hardware interrupts
				// 查看發生哪種中斷(irq)並檢查是否可以發生中斷(intctl_status) 
					begin
					intctl_epc <= mem_pc ;	
					// assign mem_pc to intctl_epc	
					intctl_status<=	{id2intctl_status[31:1],1'b0};				//disable interrupt
					// assign id2intctl_status 前 31 bit 給 intctl_status 最後補一bit 0 (intctl_status[0] = 1'b0 代表disable interrupt)
					intctl_cause <= {16'b0,irq,10'b0};
					// 把 irq 的值 放在 intctl_cause 第11~16 bit 間 前後補0補滿32bit
					iack <= 1'b1;
					// assign 1 給 iack 告訴external device，processor正在處理中斷的訊號
					end
				// set state giving the cause of  exception 
			else   
					begin
						if(if_pc == 32'h00001000)
						// 如果if_pc值為4096
							begin
							iack <= 1'b0;
							// assign 0 給 iack 告訴external device，processor沒有在處理中斷的訊號
							end
						else  intctl_epc <= intctl_epc;
						// intctl_epc不變
					end
				//
		end
endmodule
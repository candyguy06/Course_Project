`include "timescale.v"
// synopsys translate_on


module interrupt_controller(irq,rst_n,clk,if_pc,epc,status,cause,iack,in_isr);
			input [7:0]	irq;
			input 	rst_n;
			input 	clk;
			input 	if_pc;
			input 	in_isr;
			output 	epc;
			output 	cause;
			output 	status;
			output  iack;
			
			reg   	[31:0]	epc;
			reg   	[31:0]	cause;
			reg		[31:0]	status;
			wire    [31:0]	if_pc;
			wire        	in_isr;
			reg				want2isr_n;
			reg				iack;
			
			

			
		always@(negedge clk or negedge rst_n)
        begin	
			if(~rst_n)	status[31]<=1'b1;
			else if((irq[7]|irq[6]|irq[5]|irq[4]|irq[3]|irq[2]|
				    irq[1]|irq[0])&& status[31])
					begin
					epc <= if_pc;
					status[31]<=1'b0;
					iack <= 1'b1;
					end
			else   
					begin
					if(if_pc == 32'h00008200)  iack <= 1'b0;
					else	epc <= epc;
					end
		end
			
			
			
/*			
always@(negedge clk)
        begin		
			if( ( ~irqn && in_isr))
				begin
				epc <= if_pc;
				want2isr_n <= 1'b0;
				end
			else   	if (if_pc == 32'h00008200)  want2isr_n <= 1'b1;
			else	epc <= epc;
				
		end
*/
/*			
always@(negedge clk)
        begin		
			if( ( ~irqn && in_isr))
				begin
				epc <= if_pc;
				want2isr_n <= 1'b0;
				end
			else   	if (if_pc == 32'h00008200)  want2isr_n <= 1'b1;
			else	epc <= epc;
				
		end
*/
endmodule
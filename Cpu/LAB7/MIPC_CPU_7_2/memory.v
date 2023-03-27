//=====================================================================
//  (C) Copyright Chen-Chieh Wang
//  All Right Reserved
//---------------------------------------------------------------------
//  Chen-Chieh (Jay) Wang
//  http://caslab.ee.ncku.edu.tw/~jay
//---------------------------------------------------------------------
//  Computer Architecture and System Laboratory (CASLab)
//  Institute of Computer and Communication Engineering
//  National Cheng Kung University, Tainan, Taiwan.
//  http://caslab.ee.ncku.edu.tw
//---------------------------------------------------------------------
//  2010/12/28 PM. 08:51:27
//=====================================================================

// synopsys translate_off
`include "timescale.v"
// synopsys translate_on

module memory( clk,
               r_addr1,
               r_addr2,
               r_rden1,
               r_rden2,
               r_data1,
               r_data2,
               w_addr,
               w_wren,
               w_be,
               w_data
               );

        //-------------------------------------------------------------
        // Input/Output
        //-------------------------------------------------------------

        input           clk;
        input   [31:0]  r_addr1;
        input   [31:0]  r_addr2;
        input           r_rden1;
        input           r_rden2;
        output  [127:0]  r_data1;
        output  [127:0]  r_data2;
        input   [31:0]  w_addr;
        input           w_wren;
        input   [3:0]   w_be;
        input   [127:0]  w_data;

        //-------------------------------------------------------------
        // Define or Parameter
        //-------------------------------------------------------------
        parameter       MemoryName = "";        // Memory Name
        parameter       MemSize  = 32;          // Memory size in Kbytes

        //parameter     MemAddrWidth = 10;      // Memory size =  1 Kbytes
        //parameter     MemAddrWidth = 11;      // Memory size =  2 Kbytes
        //parameter     MemAddrWidth = 12;      // Memory size =  4 Kbytes
        //parameter     MemAddrWidth = 13;      // Memory size =  8 Kbytes
        //parameter     MemAddrWidth = 14;      // Memory size = 16 Kbytes
        parameter       MemAddrWidth = 15;      // Memory size = 32 Kbytes

        parameter       InitFileName = "";

        //-------------------------------------------------------------
        // Internal Wire
        //-------------------------------------------------------------
        reg     [31:0]  Mem [0:((MemSize * 256)-1)];    // Memory register array

        wire    [(MemAddrWidth-1):2]  MemAddr_R1;
        wire    [(MemAddrWidth-1):2]  MemAddr_R2;
        wire    [(MemAddrWidth-1):2]  MemAddr_W;

        reg     [127:0]  r_data1;
        reg     [127:0]  r_data2;
        reg     [31:0]  Data1;
        reg     [31:0]  Data2;
        reg     [31:0]  Data3;
        reg     [31:0]  Data4;
        integer         i;      // Loop counter used in memory initialisation

//=====================================================================
//      Main Body
//=====================================================================


        //-------------------------------------------------------------
        // initial memory
        //-------------------------------------------------------------
        initial
        begin

            for (i=0; i<=((MemSize * 256)-1); i = i+1)
                Mem[i] = 32'h0000_0000;

            if (InitFileName != "")
                begin
                $display("### Loading internal memory (%S)###", MemoryName);
                $readmemh(InitFileName, Mem);
                //$readmemb(FileName, Mem);
                end

        end


        //-------------------------------------------------------------
        // Read 1
        //-------------------------------------------------------------
        assign  MemAddr_R1 = {r_addr1[(MemAddrWidth-1):2]}; // Word address (not byte)

        always@(posedge clk)
        begin
                if(r_rden1)
                        begin
			    if(MemAddr_R1[3:2]==2'b00)
			      r_data1 <=  {Mem[MemAddr_R1+3],Mem[MemAddr_R1+2],Mem[MemAddr_R1+1],Mem[MemAddr_R1]};
			    else if(MemAddr_R1[3:2]==2'b01)
			      r_data1 <=  {Mem[MemAddr_R1+2],Mem[MemAddr_R1+1],Mem[MemAddr_R1],Mem[MemAddr_R1-1]};
			    else if(MemAddr_R1[3:2]==2'b10)
			      r_data1 <=  {Mem[MemAddr_R1+1],Mem[MemAddr_R1],Mem[MemAddr_R1-1],Mem[MemAddr_R1-2]};
			    else 
			      r_data1 <=  {Mem[MemAddr_R1],Mem[MemAddr_R1-1],Mem[MemAddr_R1-2],Mem[MemAddr_R1-3]};
			    
                        end
                else
                        r_data1 <= 128'bz;
        end

        //-------------------------------------------------------------
        // Read 2
        //-------------------------------------------------------------
        assign  MemAddr_R2 = {r_addr2[(MemAddrWidth-1):2]}; // Word address (not byte)

        always@(posedge clk)
        begin
		//不能硬往下讀4個,要辨認選擇區塊
                if(r_rden2)
                        begin
			    if(MemAddr_R2[3:2]==2'b00)
			      r_data2 <=   {Mem[MemAddr_R2+3],Mem[MemAddr_R2+2],Mem[MemAddr_R2+1],Mem[MemAddr_R2]};
			    else if(MemAddr_R2[3:2]==2'b01)
			      r_data2 <=   {Mem[MemAddr_R2+2],Mem[MemAddr_R2+1],Mem[MemAddr_R2],Mem[MemAddr_R2-1]};
			    else if(MemAddr_R2[3:2]==2'b10)
			      r_data2 <=   {Mem[MemAddr_R2+1],Mem[MemAddr_R2],Mem[MemAddr_R2-1],Mem[MemAddr_R2-2]};
			    else 
			      r_data2 <=   {Mem[MemAddr_R2],Mem[MemAddr_R2-1],Mem[MemAddr_R2-2],Mem[MemAddr_R2-3]};
			    
                        end
                else
                        r_data2 <= 128'bz;

        end

        //-------------------------------------------------------------
        // Write
        //-------------------------------------------------------------
        assign  MemAddr_W = {w_addr[(MemAddrWidth-1):2]}; // Word address (not byte)


        always@(MemAddr_W or w_wren or w_data or w_be or clk)
        begin
		//line 00
                Data1[31:24] = (w_be[3])
                                ? w_data[31:24]
                                : Mem[MemAddr_W][31:24];

                Data1[23:16] = (w_be[2])
                                ? w_data[23:16]
                                : Mem[MemAddr_W][23:16];

                Data1[15:8] = (w_be[1])
                                ? w_data[15:8]
                                : Mem[MemAddr_W][15:8];

                Data1[7:0] = (w_be[0])
                                ? w_data[7:0]
                                : Mem[MemAddr_W][7:0];
                
                //line 01
                Data2[31:24] = (w_be[3])
                                ? w_data[63:56]
                                : Mem[MemAddr_W][31:24];

                Data2[23:16] = (w_be[2])
                                ? w_data[55:48]
                                : Mem[MemAddr_W][23:16];

                Data2[15:8] = (w_be[1])
                                ? w_data[47:40]
                                : Mem[MemAddr_W][15:8];

                Data2[7:0] = (w_be[0])
                                ? w_data[39:32]
                                : Mem[MemAddr_W][7:0];
                                
                //line 10
                Data3[31:24] = (w_be[3])
                                ? w_data[95:88]
                                : Mem[MemAddr_W][31:24];

                Data3[23:16] = (w_be[2])
                                ? w_data[87:80]
                                : Mem[MemAddr_W][23:16];

                Data3[15:8] = (w_be[1])
                                ? w_data[79:72]
                                : Mem[MemAddr_W][15:8];

                Data3[7:0] = (w_be[0])
                                ? w_data[71:64]
                                : Mem[MemAddr_W][7:0];
                                
                //line 11
                Data4[31:24] = (w_be[3])
                                ? w_data[127:120]
                                : Mem[MemAddr_W][31:24];

                Data4[23:16] = (w_be[2])
                                ? w_data[119:112]
                                : Mem[MemAddr_W][23:16];

                Data4[15:8] = (w_be[1])
                                ? w_data[111:104]
                                : Mem[MemAddr_W][15:8];

                Data4[7:0] = (w_be[0])
                                ? w_data[103:96]
                                : Mem[MemAddr_W][7:0];
                

                if(w_wren&clk)//1 => MemAddr_W
                begin
                        
                        if(MemAddr_W[3:2]==2'b00)begin
			      Mem[MemAddr_W] = Data1;
			      Mem[MemAddr_W+1] = Data2;
			      Mem[MemAddr_W+2] = Data3;
			      Mem[MemAddr_W+3] = Data4;
			      end
			    else if(MemAddr_R2[3:2]==2'b01)begin
			      Mem[MemAddr_W-1] = Data1;
			      Mem[MemAddr_W] = Data2;
			      Mem[MemAddr_W+1] = Data3;
			      Mem[MemAddr_W+2] = Data4;
			      end
			    else if(MemAddr_R2[3:2]==2'b10)begin
			      Mem[MemAddr_W-2] = Data1;
			      Mem[MemAddr_W-1] = Data2;
			      Mem[MemAddr_W] = Data3;
			      Mem[MemAddr_W+1] = Data4;
			      end
			    else begin
			      Mem[MemAddr_W-3] = Data1;
			      Mem[MemAddr_W-2] = Data2;
			      Mem[MemAddr_W-1] = Data3;
			      Mem[MemAddr_W] = Data4;
			      end
                end

        end

endmodule

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
`include  "memory.v"
`include  "cpu_top.v"


// synopsys translate_on

module testbench;

    //-------------------------------------------------------------
    //      Clock Generator
    //-------------------------------------------------------------

    // Clock Cycle Time (ns)
    //parameter CCT = 100 ;     //  10.0 MHz
    //parameter CCT = 50 ;      //  20.0 MHz
    //parameter CCT = 20 ;      //  50.0 MHz
    //parameter CCT = 15 ;      //  66.0 MHz
    parameter CCT = 10 ;        // 100.0 MHz


    // Change from 1ns to 100ps to allow 0.5 ns accuracy
    parameter PERIOD =  10 * CCT;
    parameter PHASETIME = (10 * CCT)/2;
    parameter ABC = (50 * CCT);
    
    
    reg     clk;
    reg     rst_n;
    
    //cache testing
    reg [31:0] golden 	[0:38];
    reg [31:0] pattern	[0:38];


    integer exe_cycle;
    integer ins_count;
    integer i;

    initial clk=1'b0;
    initial i = 0;
    initial $readmemh("golden.dat",golden);
	

    always  #PHASETIME
            clk = ~clk;

    always  #PERIOD
            exe_cycle = exe_cycle + 1;

    //-------------------------------------------------------------
    // Define or Parameter
    //-------------------------------------------------------------

    //-------------------------------------------------------------
    //      CPU
    //-------------------------------------------------------------
    //   Interrupt  testing
	/*
	reg  [5:0]	IRQ;
	wire		IACK;
	initial    				
		begin		 IRQ=6'b000000;
        #2150   	 IRQ=6'b000001;
	//	#1600	  IRQ=8'b00000010;
		end
		
    always@(posedge clk)
		begin
			if(IACK)	IRQ<=6'b000000;
			else 		IRQ<=IRQ;
		
		end
	 */
    // Instruction memory interface signals
    wire            IREQn;          // Not Instruction Memory Request (Low active)
    wire    [31:0]  IADDR;          // Instruction Address Bus
    wire    [127:0]  IDBUS;          // Instruction Data Bus

    // Data memory interface signals
    wire            DREQn;          // Not Data Memory Request (Low active)
    wire            DWRITE;         // Data not Read (if HIGH, it is a write)
    wire    [3:0]   DBE;            // Data Memory Access Byte Enable
    wire    [31:0]  DADDR;          // Data Address Bus
    wire    [127:0]  DWDBUS;         // Data Output Bus
    wire    [127:0]  DRDBUS;         // Data Input Bus

    // Miscellaneous signals
    wire            BIGEND;         // Big-Endian Configuration
    wire            HIVECS;         // High Vectors Configuration
    wire            nWAIT;          // Not Wait

    //-------------------------------------------------------------
    //      MEM
    //-------------------------------------------------------------
    wire    [31:0]  ic_addr;
    reg     [127:0]  ic_rdatabus;
    wire            ic_rden;
    wire    [31:0]  dc_addr;
    wire    [127:0]  dc_wdatabus;
    reg     [127:0]  dc_rdatabus;
    wire            dc_wren;
    wire            dc_rden;
    wire    [3:0]   dc_be;

    wire    [31:0]  m1_ic_addr;
    wire    [127:0]  m1_ic_rdatabus;
    wire            m1_ic_rden;
    wire    [31:0]  m1_dc_addr;
    wire    [127:0]  m1_dc_wdatabus;
    wire    [127:0]  m1_dc_rdatabus;
    wire            m1_dc_wren;
    wire            m1_dc_rden;
    wire    [3:0]   m1_dc_be;

    wire    [31:0]  m2_ic_addr;
    wire    [127:0]  m2_ic_rdatabus;
    wire            m2_ic_rden;
    wire    [31:0]  m2_dc_addr;
    wire    [127:0]  m2_dc_wdatabus;
    wire    [127:0]  m2_dc_rdatabus;
    wire            m2_dc_wren;
    wire            m2_dc_rden;
    wire    [3:0]   m2_dc_be;

    wire    [31:0]  m3_ic_addr;
    wire    [127:0]  m3_ic_rdatabus;
    wire            m3_ic_rden;
    wire    [31:0]  m3_dc_addr;
    wire    [127:0]  m3_dc_wdatabus;
    wire    [127:0]  m3_dc_rdatabus;
    wire            m3_dc_wren;
    wire            m3_dc_rden;
    wire    [3:0]   m3_dc_be;

    wire    [31:0]  m4_ic_addr;
    wire    [127:0]  m4_ic_rdatabus;
    wire            m4_ic_rden;
    wire    [31:0]  m4_dc_addr;
    wire    [127:0]  m4_dc_wdatabus;
    wire    [127:0]  m4_dc_rdatabus;
    wire            m4_dc_wren;
    wire            m4_dc_rden;
    wire    [3:0]   m4_dc_be;

//=====================================================================
//      Cache
//=====================================================================	
	
	/*reg Done;
	reg Stall;
	reg CacheHit;
	reg err;*/
	

	wire           rd_mem;
	wire		   wr_mem;
	wire           d_stall_n;
	wire	[31:0] DataOut_test;
	wire    [11:0]  hitc;
	wire    [11:0]  totalc;

//=====================================================================
//      Main Body
//=====================================================================


    //-------------------------------------------------------------
    //      CPU
    //-------------------------------------------------------------
    assign  BIGEND = 1'b0 ;
    assign  HIVECS = 1'b0 ;
    assign  nWAIT  = 1'b1 ;
	
    cpu_top
        u_cpu_top(
         // System Input
         .CLK           (clk),
         .RESETn        (rst_n),
	 .IRQ 			(IRQ),
         // Instruction Memory Interface
         .IREQn         (IREQn),
         .IADDR         (IADDR),
         .IDBUS         (IDBUS),
         // Data Memory Interface
         .DREQn         (DREQn),
         .DWRITE        (DWRITE),
         .DBE           (DBE),
         .DADDR         (DADDR),
         .DWDBUS        (DWDBUS),
         .DRDBUS        (DRDBUS),
	 .BIGENDIAN		(BIGEND),
	 .IACK			(IACK),   //interrupt ack
         .dc_wren       (dc_wren),
	 .dc_rden       (dc_rden),
	 .totalc        (totalc),
	 .hitc          (hitc),
	 .DataOut_test  (DataOut_test),
	 .d_cache_stall_n (d_stall_n)
        );


    //-------------------------------------------------------------
    //      Memory Interface
    //-------------------------------------------------------------

    assign  ic_addr = IADDR ;
    assign  IDBUS = ic_rdatabus ;
    assign  ic_rden = (~IREQn) ;

    assign  dc_addr = DADDR ;
    assign  dc_wdatabus = DWDBUS ;
    assign  dc_be = DBE;
    assign  DRDBUS = dc_rdatabus;

    // assign for cache
    assign cacheRead = ~DWRITE & (~DREQn);
    assign cacheWrite = DWRITE & (~DREQn);
    
    //-------------------------------------------------------------
    //      Address Decode
    //-------------------------------------------------------------
    always@(ic_addr or
            m1_ic_rdatabus or
            m2_ic_rdatabus or
            m3_ic_rdatabus or
            m4_ic_rdatabus)
    begin

        begin
        case(ic_addr[31:24])
            8'h00:begin  ic_rdatabus = (ic_addr[23:18]==6'b0)
                                    ? m1_ic_rdatabus
                                    : 128'bz ;
					//$display("===========================================");
					end
            8'h07: ic_rdatabus = m2_ic_rdatabus;

            8'h10: ic_rdatabus = (ic_addr[23:16]==8'h00)
                                    ? m3_ic_rdatabus
                                    : 128'bz ;

            8'h20: ic_rdatabus = (ic_addr[23:16]==8'h00)
                                    ? m4_ic_rdatabus
                                    : 128'bz ;

            default:  ic_rdatabus = 128'bz ;
        endcase
        end
    end

    always@(dc_addr or
            m1_dc_rdatabus or
            m2_dc_rdatabus or
            m3_dc_rdatabus or
            m4_dc_rdatabus)
    begin
        begin
        case(dc_addr[31:24])
            8'h00: dc_rdatabus = (dc_addr[23:18]==6'b0)
                                     ? m1_dc_rdatabus
                                     : 128'bz ;

            8'h07: dc_rdatabus = m2_dc_rdatabus;

            8'h10: dc_rdatabus = (dc_addr[23:16]==8'h00)
                                     ? m3_dc_rdatabus
                                     : 128'bz ;

            8'h20: dc_rdatabus = (dc_addr[23:16]==8'h00)
                                     ? m4_dc_rdatabus
                                     : 128'bz ;

            default:  dc_rdatabus = 128'bz ;
        endcase
        end
    end

    //Memory 1
    assign  m1_ic_addr = ic_addr;
    assign  m1_ic_rden = ic_rden & (ic_addr[31:24]==8'h00)
                                 & (ic_addr[23:18]==6'b0);
    assign  m1_dc_addr = dc_addr;
    assign  m1_dc_wdatabus = dc_wdatabus;
    assign  m1_dc_wren = dc_wren & (dc_addr[31:24]==8'h00)
                                 & (dc_addr[23:18]==6'b0);
    assign  m1_dc_rden = dc_rden & (dc_addr[31:24]==8'h00)
                                 & (dc_addr[23:18]==6'b0);
    assign  m1_dc_be = dc_be;

    //Memory 2
    assign  m2_ic_addr = ic_addr;
    assign  m2_ic_rden = ic_rden & (ic_addr[31:24]==8'h07);
    assign  m2_dc_addr = dc_addr;
    assign  m2_dc_wdatabus = dc_wdatabus;
    assign  m2_dc_wren = dc_wren & (dc_addr[31:24]==8'h07);
    assign  m2_dc_rden = dc_rden & (dc_addr[31:24]==8'h07);
    assign  m2_dc_be = dc_be;

    //Memory 3
    assign  m3_ic_addr = ic_addr;
    assign  m3_ic_rden = ic_rden & (ic_addr[31:24]==8'h10)
                                 & (ic_addr[23:16]==8'h00);
    assign  m3_dc_addr = dc_addr;
    assign  m3_dc_wdatabus = dc_wdatabus;
    assign  m3_dc_wren = dc_wren & (dc_addr[31:24]==8'h10)
                                 & (dc_addr[23:16]==8'h00);
    assign  m3_dc_rden = dc_rden & (dc_addr[31:24]==8'h10)
                                 & (dc_addr[23:16]==8'h00);
    assign  m3_dc_be = dc_be;


    //Memory 4
    assign  m4_ic_addr = ic_addr;
    assign  m4_ic_rden = ic_rden & (ic_addr[31:24]==8'h20)
                                 & (ic_addr[23:16]==8'h00);
    assign  m4_dc_addr = dc_addr;
    assign  m4_dc_wdatabus = dc_wdatabus;
    assign  m4_dc_wren = dc_wren & (dc_addr[31:24]==8'h20)
                                 & (dc_addr[23:16]==8'h00);
    assign  m4_dc_rden = dc_rden & (dc_addr[31:24]==8'h20)
                                 & (dc_addr[23:16]==8'h00);
    assign  m4_dc_be = dc_be;

    //-------------------------------------------------------------
    //  Code Memory = 256KB (0x0000_0000 ~ 0x0003_FFFF)
    //-------------------------------------------------------------
    defparam u_code_memory.MemoryName       = "Code";       // Memory Name
    defparam u_code_memory.MemSize          = 256;          // Memory size in Kbytes
    defparam u_code_memory.MemAddrWidth     = 18;
    defparam u_code_memory.InitFileName     = "software_mips/code.mif";

    memory          u_code_memory(
                     .clk           (clk),
                     .r_addr1       (m1_ic_addr),
                     .r_addr2       (m1_dc_addr),
                     .r_rden1       (m1_ic_rden),
                     .r_rden2       (m1_dc_rden),
                     .r_data1       (m1_ic_rdatabus),
                     .r_data2       (m1_dc_rdatabus),
                     .w_addr        (m1_dc_addr),
                     .w_wren        (m1_dc_wren),
                     .w_be          (m1_dc_be),
                     .w_data        (m1_dc_wdatabus)
                    );


    //-------------------------------------------------------------
    //  Stack Memory = 16384KB (0x0700_0000 ~ 0x07FF_FFFF)
    //-------------------------------------------------------------
    defparam u_stack_memory.MemoryName      = "Stack";      // Memory Name
    defparam u_stack_memory.MemSize         = 16384;        // Memory size in Kbytes
    defparam u_stack_memory.MemAddrWidth    = 24;
    defparam u_stack_memory.InitFileName    = "";

    memory          u_stack_memory(
                     .clk           (clk),
                     .r_addr1       (m2_ic_addr),
                     .r_addr2       (m2_dc_addr),
                     .r_rden1       (m2_ic_rden),
                     .r_rden2       (m2_dc_rden),
                     .r_data1       (m2_ic_rdatabus),
                     .r_data2       (m2_dc_rdatabus),
                     .w_addr        (m2_dc_addr),
                     .w_wren        (m2_dc_wren),
                     .w_be          (m2_dc_be),
                     .w_data        (m2_dc_wdatabus)
                    );

    //-------------------------------------------------------------
    //  Input Data Memory = 64KB (0x1000_0000 ~ 0x1000_FFFF)
    //-------------------------------------------------------------
    defparam u_input_memory.MemoryName      = "InputData";  // Memory Name
    defparam u_input_memory.MemSize         = 64;           // Memory size in Kbytes
    defparam u_input_memory.MemAddrWidth    = 16;
    defparam u_input_memory.InitFileName  = "software_mips/data.mif";

    memory          u_input_memory(
                     .clk           (clk),
                     .r_addr1       (m3_ic_addr),
                     .r_addr2       (m3_dc_addr),
                     .r_rden1       (m3_ic_rden),
                     .r_rden2       (m3_dc_rden),
                     .r_data1       (m3_ic_rdatabus),
                     .r_data2       (m3_dc_rdatabus),
                     .w_addr        (m3_dc_addr),
                     .w_wren        (m3_dc_wren),
                     .w_be          (m3_dc_be),
                     .w_data        (m3_dc_wdatabus)
                    );

    //-------------------------------------------------------------
    //  Output Data Memory = 64KB (0x2000_0000 ~ 0x2000_FFFF)
    //-------------------------------------------------------------
    defparam u_output_memory.MemoryName     = "OutputData"; // Memory Name
    defparam u_output_memory.MemSize        = 64;           // Memory size in Kbytes
    defparam u_output_memory.MemAddrWidth   = 16;
    defparam u_output_memory.InitFileName   = "";


    memory          u_output_memory(
                     .clk           (clk),
                     .r_addr1       (m4_ic_addr),
                     .r_addr2       (m4_dc_addr),
                     .r_rden1       (m4_ic_rden),
                     .r_rden2       (m4_dc_rden),
                     .r_data1       (m4_ic_rdatabus),
                     .r_data2       (m4_dc_rdatabus),
                     .w_addr        (m4_dc_addr),
                     .w_wren        (m4_dc_wren),
                     .w_be          (m4_dc_be),
                     .w_data        (m4_dc_wdatabus)
                    );


//=====================================================================
//      Monitor
//=====================================================================



    //------------------------
    //  dCache dataout test
    //------------------------
    
    always@( posedge d_stall_n )
    begin
      
      if(i<37)begin
    
	  if(i==0) i = 1;
	  else
	  begin
	    pattern[i] = DataOut_test[31:0];
	
		if(pattern[i]==golden[i-1])
		    $display("      CacheDataOutput #%d is correct   ", i);
		else
		    $display("      CacheDataOutput #%d is wrong     ", i);
	
		i = i + 1;
	 end
	end
    end
    

    //-------------------------------------------------------------
    //  Dynamic Ins. Number Count
    //-------------------------------------------------------------
    always@(posedge clk)
    begin

        begin

        if(exe_cycle<=7)
                ins_count = 1;
//        else if(u_cpu_top.u_cpu_core.u_cpuid.interlock==1)
//                ;//NOP
//        else if(u_cpu_top.u_cpu_core.u_cpuid.id_bubble==1)
//                ;//NOP
        else
                ins_count = ins_count + 1 ;
        end
    end

    //-------------------------------------------------------------
    //  Processing
    //-------------------------------------------------------------
    always@(posedge clk)
    begin

        if(exe_cycle%10000==0)
            $display("      Execution Cycle = %d", exe_cycle);
        else
            ;//NOP
    end

    //-------------------------------------------------------------
    //  Checking Memory Access Error
    //-------------------------------------------------------------
    //  Code Memory         = 256KB   (0x0000_0000 ~ 0x0003_FFFF)
    //  Stack Memory        = 16384KB (0x0700_0000 ~ 0x07FF_FFFF)
    //  Input Data Memory   = 64KB    (0x1000_0000 ~ 0x1000_FFFF)
    //  Output Data Memory  = 64KB    (0x2000_0000 ~ 0x2000_FFFF)

    //Instruction Fetch
    always@(posedge clk)
    begin
        if(IADDR==32'h00000074)
            $display("      SWI => Self-Loop");
        else if(IADDR==32'hF0000000)
            begin
            ins_count = ins_count-9;

            exe_cycle = exe_cycle-16;
            

            $display("===========================================");
            $display("      Program terminated normally");
            $display("===========================================");
            $display("      Dynamic Instruction Number = %d", ins_count);
            $display("      Execution Cycle = %d", exe_cycle);
            $display("===========================================");
            $display("      Total cache read/write conditions = %d", totalc);
            $display("      Hits = %d", hitc);
            $stop;
            end
        else if((IREQn==1'b0)&(m1_ic_rden==1'b0))
            begin
            $display("===========================================");
            $display("      Instruction Fetch Error!             ");
            $display("===========================================");
            $display("      Memory Address = %h", IADDR);
            $display("      Execution Cycle = %d", exe_cycle);
            $display("===========================================");
            $stop;
            end
        else
            ;//NOP
    end
/*
    //Data Access
    always@(posedge clk)
    begin
        if(DREQn==1'b0)
            begin
            if(DWRITE==1'b1) //Write
                begin
                if(~(m1_dc_wren|m2_dc_wren|m3_dc_wren|m4_dc_wren))
                    begin
                    $display("===========================================");
                    $display("      Write Memory Error!                  ");
                    $display("===========================================");
                    $display("      Memory Address = %h", DADDR);
                    $display("      Execution Cycle = %d", exe_cycle);
                    $display("===========================================");
                    $stop;
                    end
                else
                    ;//NOP
                end
            else //Read
                begin
                if(~(m1_dc_rden|m2_dc_rden|m3_dc_rden|m4_dc_rden))
                    begin
                    $display("===========================================");
                    $display("      Read Memory Error!                   ");
                    $display("===========================================");
                    $display("      Memory Address = %h", DADDR);
                    $display("      Execution Cycle = %d", exe_cycle);
                    $display("===========================================");
                    $stop;
                    end
                else
                    ;//NOP
                end
            end
        else
            ;//NOP
    end
*/

    //-------------------------------------------------------------
    //  Reset
    //-------------------------------------------------------------
    initial
    begin

            rst_n=1'b0;

            #(PERIOD)
            exe_cycle=0;

            #(PHASETIME)
            rst_n=1'b1;

    //-------------------------------------------------------------
    //  Check Point
    //-------------------------------------------------------------
            //while(exe_cycle!=30391) #PERIOD;
            //$stop;

            //while(exe_cycle!=30263) #PERIOD;
            //$stop;
            //
            //while(exe_cycle!=30264) #PERIOD;
            //$stop;
            //
            //while(exe_cycle!=30265) #PERIOD;
            //$stop;
            //
            //while(exe_cycle!=30266) #PERIOD;
            //$stop;
            //
            //while(exe_cycle!=30267) #PERIOD;
            //$stop;
            //
            //while(exe_cycle!=60000) #PERIOD;
            //$stop;
            
	    while(exe_cycle!=3000) #PERIOD;
	    $display("===========================================");
            $display("      Program terminated normally");
            $display("===========================================");
            $display("      Total cache read/write conditions = %d", totalc);
            $display("      Hits = %d", hitc);
            $display("===========================================");
            $stop;
            
    end

endmodule



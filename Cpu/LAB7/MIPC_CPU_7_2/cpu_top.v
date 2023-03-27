/*`include "timescale.v"
`include  "cpu_control_unit.v"
`include  "cpu_core.v"
`include  "cpu_ex.v"
`include  "cpu_ex_alu.v"
`include  "cpu_ex_alu_adder.v"
`include  "cpu_ex_alu_clo.v"
`include  "cpu_ex_alu_shifter.v"
`include  "cpu_ex_forward_unit.v"
`include  "cpu_id.v"
`include  "cpu_id_adder.v"
`include  "cpu_id_branch_unit.v"
`include  "cpu_id_forward_unit.v"
`include  "cpu_id_hdu.v"
`include  "cpu_id_reg32_ne.v"
`include  "cpu_id_regbank.v"
`include  "cpu_if.v"
`include  "cpu_mem.v"
`include  "cpu_wb.v" */

//`include  "I_Cache.v"
`include  "dcache_system.v"
    
module  cpu_top(
         // System Input
         CLK,
         RESETn,
		 IRQ,
         // Instruction Memory Interface
         IREQn,
         IADDR,
         IDBUS,
         // Data Memory Interface
         DREQn,
         DWRITE,
         DBE,
	 DADDR,
         DWDBUS,
         DRDBUS,
	 BIGENDIAN,
         IACK,   //interrupt  ack
         hitc,
         totalc,
         DataOut_test,
         d_cache_stall_n,
	 dc_wren,
	 dc_rden
        );

	    //-------------------------------------------------------------
        //      System I/O signals
        //-------------------------------------------------------------
        input           CLK;		// System Clcok
        input           RESETn;		// System Reset (Low active)
	input   [5:0]   IRQ;       // Interrupt


		//-------------------------------------------------------------
        //	Instruction memory interface signals 
        //-------------------------------------------------------------
        output		IREQn;		// Instruction Memory Request
        output  [31:0]  IADDR;		// Instruction Address Bus
        input	[127:0]	IDBUS;		// Instruction Data Bus       

        //-------------------------------------------------------------
        //      Data memory interface signals 
        //-------------------------------------------------------------
        output		DREQn;		// Data Memory Request
        output		DWRITE;		// Data Memory Access Direction
        output	[3:0]	DBE;		// Data Memory Byte Enable
        output	[31:0]	DADDR;		// Data Address Bus
        output	[127:0]	DWDBUS;		// Data Write Bus
	input	[127:0]	DRDBUS;		// Data Read Bus
		//-------------------------------------------------------------
        //     Control interface signals
        //-------------------------------------------------------------   
        input		BIGENDIAN;	// [1]Big-Endian or 
                                        // [0]Little-Endian
	output			IACK;
	output	[11:0]		totalc;
	output	[11:0]		hitc;
	output	[31:0]  	DataOut_test;
	output			d_cache_stall_n;
	output           dc_wren;
	output           dc_rden;
		
		
	wire 			DREQ;
	wire			IREQ;	
	wire 			IACK;
	wire			DWRITE;
	wire			I_Cache_REQ;
	wire	[31:0]		DC_ADDR;
	wire    [31:0]		DC_DWDBUS;
	wire    [31:0]		DC_DRDBUS;
	wire	[31:0]		I_Cache_ADDR;
	wire	[31:0]		I_Cache_DBUS;
	wire			i_cache_stall_n;
	wire			d_cache_stall_n;
	wire			wr_mem;
	wire			rd_mem;
	wire			cacheWrite;
	wire			cacheRead;
	wire	[127:0]		CacheDataOut;
										
	assign 		DREQn = ~DREQ ;	
	assign 		IREQn = ~IREQ ;		
	
	//d-cache
	assign cacheRead = ~DWRITE & (~DREQn);
    assign cacheWrite = DWRITE & (~DREQn);
	assign  dc_wren = (~DREQn) & wr_mem ;
	assign  dc_rden = (~DREQn) & rd_mem ;
	assign  DWDBUS = (dc_wren)? CacheDataOut: 127'b0;
	assign  DC_DRDBUS =  (DC_ADDR[3:2] == 2'b00) ? CacheDataOut[31:0] :
			     (DC_ADDR[3:2] == 2'b01) ? CacheDataOut[63:32]:
			     (DC_ADDR[3:2] == 2'b10) ? CacheDataOut[95:64]:
						       CacheDataOut[127:96];
		
cpu_core u_cpu_core(
	
        // System input signals
        .CLK		(CLK),		// (I) System Clock
        .RESETn		(RESETn),		// (I) System Reset (Low active)
	.IRQ 	 	(IRQ),         //interupt  
	.i_cache_stall_n      (i_cache_stall_n),
	.d_cache_stall_n      (d_cache_stall_n),

        // Instruction memory interface signals 
        .IREQ		(I_Cache_REQ),		// (O) Instruction Memory Request
        .IADDR		(I_Cache_ADDR),		// (O) Instruction Address Bus
        .IDBUS		(I_Cache_DBUS),		// (I) Instruction Data Bus
        
        // Data memory interface signals 
        .DREQ		(DREQ),		// (O) Data memory REQuest
        .DWRITE		(DWRITE),		// (O) Data Memory Access Direction
        .DBE		(DBE),		// (O) Data Memory Access Size
        .DADDR		(DC_ADDR), 		// (O) Data Address Bus
        .DWDBUS		(DC_DWDBUS),		// (O) Data Write Bus
        .DRDBUS		(DC_DRDBUS),		// (I) Data Read Bus 
        
        // Control interface signals
        .BIGENDIAN	(BIGENDIAN),	// (I) Big or Little Endian 
	.IACK		(IACK)


		
        );
I_Cache u_i_cache(
		.clk		(CLK),	
		.rst_n		(RESETn),
		.CSn		(I_Cache_REQ),//(I)
		.ADDR		(I_Cache_ADDR),//(I)
		.DO		(I_Cache_DBUS),//(O)
		
		.IREQ		(IREQ),//
		.IADDR		(IADDR),//
		.data_in	(IDBUS),//
		
		.cache_stall_n	(i_cache_stall_n)
);

     dcache_system #(9) dcache1(
	      .req(DREQn),//from cpu
	      .Addr(DC_ADDR),//from cpu                Addr
	      .rst(~RESETn),
	      .Rd(cacheRead),//from cpu
	      .Wr(cacheWrite),//from cpu
	      .clk(CLK),//from cpu
	      .DataIn(DC_DWDBUS),//from cpu                DataIn
	      .data_out_mem(DRDBUS),//from memory                 data_in_cache
	      .addr_mem(DADDR),//to memory  (addr)          addr_mem
	      .DataOut(CacheDataOut),//to memory   (data)   to cpu (data)  DataOut
	      .Stall_n(d_cache_stall_n),
	      .wr_mem(wr_mem),
	      .rd_mem(rd_mem),
	      .hitc(hitc),
	      .totalc(totalc),
	      .DataOut_test(DataOut_test)
                
	);
		
	endmodule

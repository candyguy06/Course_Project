// top module
`timescale 100ps/1ps
module dcache_system(
   // Outputs
   DataOut, Stall_n, addr_mem, wr_mem, rd_mem, hitc, totalc, DataOut_test,
   // Inputs
   req, Addr, DataIn, Rd, Wr, clk, rst, data_out_mem
   );
   parameter         index_size = 2;  // overridden for each cache instance
   input [31:0] Addr;        // 來自cpu的data address 
   input [31:0] DataIn;     //  來自cpu的data 
   input        Rd;
   input        Wr;
   input        clk;
   input        rst;
   input        req;
   
   input [127:0] data_out_mem;
   
   output [127:0] DataOut;     //D-cache data 輸出
   output Stall_n;                //輸出給 cpu的stall_n
   output [31:0] DataOut_test;       //除去stall時的output , 也就是實際上cpu看到的cache dataout
   
   
   //new
   output [31:0] addr_mem;		//to memory 
   output wr_mem;
   output rd_mem;

   output [11:0] hitc; // 紀錄cache hit次數
   output [11:0] totalc;//紀錄總共作幾次cache存取



	/* internal signal */
	wire wr_cache, valid_in, sel_data_cache; // for cache
	wire wr_mem, rd_mem, sel_tag_mem; // for main memory

	wire all_line;


	wire enable, err_cache;
	//
	wire [index_size-1:0] index;
	wire [27-index_size:0] tag_in, tag_out;
	wire [1:0]	line;
	//
	wire [127:0] data_in_cache;
	wire [127:0] cpu_data_in;
	
	
	wire [31:0] addr_mem;
	wire [127:0] data_out_mem, data_out_mem_late;
	wire [3:0] busy;
	wire Stall_mem, err_mem, Stall;

	wire change;
	wire numout;
	wire [27-index_size:0] tag_mem;
	wire datahiz;
	wire [3:0]  cs;
	wire cacheWR;
	wire [11:0] hitc;
	wire [11:0] totalc;
	wire cache_write;
	wire m_change, change1, change2, change3, change4, change5, change_state ;
	wire dirty_in, dirty_check, write_back;
	wire [1:0] line_temp;

	
	
	//////////////////////////////////////////////////// Edit Here
	
    // 依需求把Addr訊號線拆成index, line, tag_in 
    assign line = Addr[3:2] ; // line is 2 bits	
	assign index = Addr[index_size+3:4] ; // index size is decided by the parameter "index_size"
	assign tag_in = Addr[31:index_size+4] ; // You can get the tag_in after determined the line and index
	assign addr_mem = {tag_mem, index, line[1:0], 2'b00}; // the address send to memory


	//////////////////////////////////////////////////// Edit Here
	
	
	
    
	count count1 (.go(m_change), .change(change1), .clk(clk), .rst(rst));
	count count2 (.go(change1), .change(change2), .clk(clk), .rst(rst));
	count count3 (.go(change2), .change(change3), .clk(clk), .rst(rst));
	count count4 (.go(change3), .change(change4), .clk(clk), .rst(rst));
	count count5 (.go(change4), .change(change_state), .clk(clk), .rst(rst));
	
	
	latency data_read(.clk(clk), .rst(rst), .go_in(change1), .go_out(change4), .data_in(data_out_mem), .data_out(data_out_mem_late));

	assign cpu_data_in = (line == 2'b00) ? {96'bz, DataIn[31:0]} :
			     (line == 2'b01) ? {64'bz, DataIn[31:0], 32'bz} :
			     (line == 2'b10) ? {32'bz, DataIn[31:0], 64'bz} :
					       {DataIn[31:0], 96'bz};
	
	// 1 - from main mem, 0 - from primary input
	assign data_in_cache = sel_data_cache ? data_out_mem_late : cpu_data_in;
    // read from memory to cache, delay offset for 2cycle to write into cache
    // write data to memroy, offsets for cache and memory are synchronous

	// 1 - from tag_out, 0 - from primary input
	assign tag_mem = sel_tag_mem ? tag_out : tag_in;//決定addr_mem中的tag_mem從cache(tag_out)來還是從cpu來(tag_in)

	assign enable = ~rst;
	
	assign Stall_n = ~Stall;
	
	assign cacheWR = ((cs==4'd3)|(cs==4'd7))? 1:0 ;//代表要寫入cache的情形
	
	assign  DataOut_test =  (Stall)? 127'bz :
				(line_temp == 2'b00) ? DataOut[31:0] :
			        (line_temp == 2'b01) ? DataOut[63:32]:
			        (line_temp == 2'b10) ? DataOut[95:64]:
						       DataOut[127:96];
	
	assign cache_write = wr_cache  ;
	
	assign m_change = rd_mem ;
	
	assign dirty_check = dirty_in ;

	assign write_back = (cs==4'd10)? 1:0;
	

        //hit 計數
	hitrate hitcount(.hitc(hitc), .totalc(totalc), .cs(cs), .rst(rst), .clk(clk));//hit數計數
	
	
	//cache state控制
	dcache_ctrl ctrl_unit(
	/* input */
	.Rd(Rd), .Wr(Wr), .hit(hit),  .valid(valid),
	.clk(clk), .rst(rst), .mem_change(change_state), .req(req), .dirty(dirty),
	/* output */
	.wr_cache(wr_cache), .valid_in(valid_in), .sel_data_cache(sel_data_cache),
	.wr_mem(wr_mem), .rd_mem(rd_mem), .sel_tag_mem(sel_tag_mem), //.offset(offset_mem),
	.stall(Stall), .datahiz(datahiz), .cs(cs),
	.all_line(all_line), .dirty_in(dirty_in) // output Done, CacheHit, Stall
	);
	//write在neg edge就要拉下
	dcache #(index_size) c0 (
		/* input */
		.enable(enable), .clk(clk), .rst(rst),
		.tag_in(tag_in), .index(index), 
		.data_in(data_in_cache), .write(cache_write), .valid_in(valid_in),.datahiz(datahiz),
		.line(line), .all_line(all_line), .dirty_in(dirty_check),
		.tag_out(tag_out), .data_out(DataOut), // output DataOut
		.hit(hit),  .valid(valid), .dirty(dirty), .line_temp(line_temp)
	);


   

endmodule // mem_system


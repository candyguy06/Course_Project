module dcache (
              enable,
              clk,
              rst,
              tag_in,
              index,
              line,
              data_in,
              write,
              valid_in,
	      datahiz,
	      all_line,
              tag_out,
              data_out,
              hit,
              valid,
              dirty,
              dirty_in,
              line_temp

              );

   parameter         index_size = 0;  // overridden for each cache instance

   
   input enable;
   input clk;
   input rst;
   input [27-index_size:0] tag_in;
   input [index_size-1:0] index;
   input [1:0] line;
   input [127:0] data_in;
   input write;
   input valid_in;
   input datahiz;
   input all_line;
   input dirty_in;
   output [27-index_size:0] tag_out;
   output [127:0] data_out;
   output hit;
   output valid;
   output dirty;
   output [1:0] line_temp;
   wire  [31:0] c1_data_out;
   wire  [31:0] c2_data_out;
   wire  [31:0] c3_data_out;
   wire  [31:0] c4_data_out;
   wire  [31:0] data_in1;
   wire  [31:0] data_in2;
   wire  [31:0] data_in3;
   wire  [31:0] data_in4;
   reg   [index_size-1:0] index_temp;
   reg   [1:0] line_temp;
   wire	 valid_temp;
   wire	 dirty_temp;

   
   always@(posedge clk or posedge rst)begin
   
		if(rst)begin
				index_temp <= 11'b0;
				line_temp  <= 2'b0;
				end
			else begin
				index_temp <= index;
				line_temp  <= line;

			end
				
				
		
		
   
   end
   
   assign            go = enable & ~rst;
   assign            match = (tag_in == tag_out);

   assign 			 valid_temp = 1;
   assign			 dirty_temp = 1;
   assign            wr_data1  = ( go & write & (line==2'b00) ) | all_line;
   assign            wr_data2  = ( go & write & (line==2'b01) ) | all_line;
   assign            wr_data3  = ( go & write & (line==2'b10) ) | all_line;
   assign            wr_data4  = ( go & write & (line==2'b11) ) | all_line;
   
   assign            wr_tag   = go & write ;

   

						     
   assign	     data_out = (datahiz) ? 128'bz : {c4_data_out[31:0], c3_data_out[31:0], c2_data_out[31:0], c1_data_out[31:0]};


   assign data_in1 = data_in[31:0];

					    
   assign data_in2 = data_in[63:32];

					    
   assign data_in3 = data_in[97:64];
					  
					  
   assign data_in4 = data_in[127:96];

   //line:00
   memc #(32) 		 mem_w1 (c1_data_out,index_temp, data_in1, wr_data1, clk, rst);

   //line:01
   memc #(32) 		 mem_w2 (c2_data_out,index_temp, data_in2, wr_data2, clk, rst);

   //line:10
   memc #(32) 		 mem_w3 (c3_data_out,index_temp, data_in3, wr_data3, clk, rst);

   //line:11
   memc #(32) 		 mem_w4 (c4_data_out,index_temp, data_in4, wr_data4, clk, rst);
   
   //tag
   memc #(28-index_size) mem_tg (tag_out, index_temp, tag_in,   wr_tag,   clk, rst);
   
   //valid
   memv 		 mem_vl (validbit,index_temp, valid_temp, valid_in, clk, rst);
   
   //drity bit
   memv 		 mem_db (dirtybit,index_temp, dirty_temp, dirty_in, clk, rst);   

   assign            hit = go & match & validbit;

   assign            valid = go & validbit ;
   
   assign	     dirty = go & dirtybit ;

endmodule


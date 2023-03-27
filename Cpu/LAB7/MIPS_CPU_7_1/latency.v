/* 
(C) OOMusou 2008 http://oomusou.cnblogs.com

Filename    : d_ff.v
Compiler    : Quartus II 7.2 SP3
Description : Demo how to write d flip-flop
Release     : 08/09/2008 1.0
*/

module latency (
  input      clk,
  input      rst,
  input      go_in,
  input      go_out, 
  input  [127:0]    data_in,
  output reg [127:0] data_out
);


  reg  [127:0] temp ;
  
    

    always @(posedge clk or posedge rst) begin
      if(rst) begin
			temp <= 128'bz;
			data_out <= 128'bz;
			end
		else begin
		if(go_in)begin
			temp <= data_in;
			data_out <= data_out;	
			end 
		else if(go_out)begin
			temp <= 128'bz;
			data_out <= temp;
			end else begin
			temp <= temp;
			data_out <= 128'bz;	
			end
		end
    end//rst
    
    
endmodule
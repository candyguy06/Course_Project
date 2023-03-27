// change_signal
`timescale 100ps/1ps
module change_signal (change, data, clk, rst, en);

    output         change;
    input  [31:0]  data;
    input          clk;
    input          rst;
	input          en; 
	


	//reg    [31:0]  pre;
    reg    [31:0]  temp;
	reg    change;

	//wire en_in;
	
	//assign en_in = en & control;
	
   

	
	
	
    always @(posedge clk) begin
 
	  if(rst)begin
				temp <= 32'bz;
				change <= 0;
				end
	   else begin
			temp <= data ;
			if(change==1)begin
				change <= 0;
			end else
			if(data != temp)begin
				change <= 1;
			end else change <= 0;
			
			
			end
	   
    end
endmodule



`timescale 100ps/1ps
module count (go, change, clk, rst);

    output         change;
    input          go;
    input          clk;
    input          rst;

    reg    [1:0]   count;

	assign change = (count == 0) ? 1 : 0 ;
    

    always @(posedge clk or posedge rst) begin
      if(rst) begin
			count <= 2'd1;
			end
		else begin
		if(go)begin
			if(count!=0)begin
				count <= count - 2'd1;
				end 
				else begin
				count <= 2'd0;
					end
			end 
		else begin
			count <= 2'd1;
			end
		end
    end//rst
		

endmodule

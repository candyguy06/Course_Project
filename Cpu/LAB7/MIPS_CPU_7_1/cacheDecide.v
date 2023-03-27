
`timescale 100ps/1ps
module cacheDecide (numout ,cacheWR, rst);

    output         numout;
    input          cacheWR;
    input          rst;

    reg            numout;


    always @(posedge cacheWR or posedge rst) begin
      if(rst) begin
			numout <= 1'd0;
			end
		else begin
				if(numout==0)
					numout = 1;
				else
					numout = 0;
			end
		
    end
		

endmodule


`timescale 100ps/1ps
module cacheDecide (numout , cacheWR, valid1, valid2, match1, match2, rst, cs);

    output         numout;
    input          rst, cacheWR;
    input [3:0]	   cs;
    input	   valid1, valid2, match1, match2;

    reg            numout, temp;
    wire	   done;
    assign	   done = (cs == 4'd0);

    always @(posedge rst or posedge cacheWR or posedge done or posedge match1 or posedge match2)begin
      if(rst)begin
	numout <= 1'd0;
	temp   <= 1'd0;
      end else begin
	if(cacheWR)begin
			  if( !valid1 & valid2)
				    temp <= 0;
				else if(valid1 & !valid2)
				    temp <= 1;
				else if(valid1 & valid2)begin
					if(match1 & !match2)
					  temp <= 0;
					else if(!match1 & match2)
					  temp <= 1;
					else
					  temp <= ~temp;
					  
				end else
				  
				    temp <= ~temp;
	end else if(done)begin
	  numout <= temp;
	end
      end
    end
    
   /* always @( posedge rst or posedge match1 or posedge match2) begin
      if(rst) begin
			numout <= 1'd0;
			end
		else begin*/
				/*numout <= (~valid1)? 1'b0 :
					  (~valid2)? 1'b1 :
					  (match1)?  1'b0 :
					  (match2)?  1'b1 :
					  (numout )? 1'b0 :
						     1'b1 ;*/
				/*if( !valid1 & valid2)
				    numout <= 0;
				else if(valid1 & !valid2)
				    numout <= 1;
				else if(valid1 & valid2)begin
					if(match1 & !match2)
					  numout <= 0;
					else if(!match1 & match2)
					  numout <= 1;
					else
					  numout <= ~numout;
					  
				end else
				  
				    numout <= ~numout;
			end
		
    end*/
		

endmodule

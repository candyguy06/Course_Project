module Decoder (
              addr,
              Op,
              Rs,
              Rt,
              Rd,
              Shamt,
              Func,
              offset
              );
	input [31:0] addr ;
	output reg [6:0] Op;
	output reg [5:0] Rs;
	output reg [5:0] Rt;
	output reg [5:0] Rd;
	output reg [5:0] Shamt;
	output reg [6:0] Func;
	output reg [15:0] offset;

	always@(*)	begin
		Op = addr[31:27] ;
		Rs = addr[26:22] ;
		Rt = addr[21:17] ;
		Rd = addr[16:12] ;
		Shamt = addr[11:7] ;
		Func = addr[6:0] ;
		offset = addr[15:0] ;

	end

endmodule


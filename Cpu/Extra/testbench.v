module testbench();
	reg [31:0] addr	;
	wire [6:0] Op	;
	wire [5:0] Rs	;
	wire [5:0] Rt	;
	wire [5:0] Rd	;
	wire [5:0] Shamt	;
	wire [6:0] Func	;
	wire [15:0] offset	;

//	assign addr = 32'b00000000100011000010111000101011 ;

	Decoder d1(
	.addr(addr),
	.Op(Op),
	.Rs(Rs),
	.Rt(Rt),
	.Rd(Rd),
	.Shamt(Shamt),
	.Func(Func),
	.offset(offset)
	) ;

	initial 
	begin
		#20
		addr <= 32'b 00000011111001110100100000000011;
		#20
		addr <= 32'b 10001100001010000000000000100000;	  
		#20
		addr <= 32'b 00011000101010000010100000101000;
		#20
		addr <= 32'b 00001000101011001010111010101011;
	end


endmodule



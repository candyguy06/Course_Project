// Ram Memory for I Cache
`define IndexWidth 10
`define CacheDepth 1024

`include "timescale.v"

module Cache_Ram(
	// signals to I Chche (tag:check;word:data)
	data_out,
	
	// signals from I Cache address
	index,

	// signals from I Chche (tag:check;word:data)
	data_in,

	// signals from I Cache Controller 
	write,
);

	// from I Cache, used to set the number of bits of the memory
	parameter BitSize = 1;
	output [BitSize-1:0]		data_out;
	input  [`IndexWidth-1:0]	index;
	input  [BitSize-1:0]		data_in;
	input						write;

	// creat memory for I Cache
	reg [BitSize-1:0]	Ram [0:`CacheDepth-1];
	
	integer i;

//-----------------------------------------------
// Begining of main code
//-----------------------------------------------


	assign data_out=(~write)?Ram[index]:0;
	
	always@(write)
	begin
	if(write)
		begin
			Ram[index]=data_in;	
		end
	end


	initial
	begin
		for(i=0;i<`CacheDepth;i=i+1)
		begin
			Ram[i] = 0;
		end
	end

endmodule
		


	
	

	

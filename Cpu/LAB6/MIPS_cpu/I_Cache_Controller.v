// I Cache Controller 
`define ADDRWIDTH 32

`include "timescale.v"

module I_Cache_Controller(
	// signals used during normal operation 
	clk,
	RA,

	// signals from I_cache
	Cache_En,
	Cache_Hit,
	fill_finish,

	// signals to I_Cache
	WEn,
	REn,
	OEn
);

	// signals used during normal operation 
	input		clk;
	input [`ADDRWIDTH-3:0]	RA;

	// signals from I_cache
	input		Cache_En;
	input		Cache_Hit;

	// signals to I_Cache
	output 		WEn;
	output		REn;
	output		OEn;
	output		fill_finish;

  
	// FSM Register
	reg [2:0]	state;
	reg [2:0]	next_state;
	reg [4:0]	counter;		// simulate Miss delay 

//-----------------------------------------------
// Constant declarations
//-----------------------------------------------
	`define ICache_IDLE		3'd0
	`define ICache_Compare		3'd1
	`define ICache_Hit		3'd2
	`define ICache_Miss		3'd3

//-----------------------------------------------
// Begining of main code
//-----------------------------------------------

	assign	OEn = (state==2)? 1'b1:1'b0;	
	assign	REn = (state==1 || state==2) ? 1'b1:1'b0;
	assign	WEn = (state==3)? 1'b1:1'b0;
	assign  fill_finish = (WEn && counter==2)? 1'b1:1'b0;

// FSM

		always@(RA or Cache_En)
		begin
			state<=`ICache_IDLE;
			next_state<=`ICache_IDLE;
		end
	

	always@(posedge clk)
	begin
		state<=next_state;
		
		if(WEn)				// simulate the delay of Miss State
		begin
			counter=counter+1;
		end
	
	end

	always@(RA or counter==3)
	begin
		counter=0;
	end

	always@(Cache_En or fill_finish or Cache_Hit or posedge clk)

	begin
		case(state)
			`ICache_IDLE:
			begin
				next_state=(Cache_En)?`ICache_Compare:`ICache_IDLE;
			end
			`ICache_Compare:
			begin
				next_state=(Cache_Hit)?`ICache_Hit:`ICache_Miss;
			end
			`ICache_Hit:
			begin
				next_state=`ICache_Hit;
			end
			`ICache_Miss:
			begin
				next_state=(fill_finish)?`ICache_Hit:`ICache_Miss;
			end
			default:
			begin
				next_state=`ICache_IDLE;
			end
		endcase
	end

endmodule

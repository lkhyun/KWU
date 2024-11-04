module os_logic(state, d_in, d_out); //FSM output logic 
	
	parameter	IDLE_STATE 	= 3'b000; //count = 0 
	parameter	LOAD_STATE 	= 3'b001; //load input data to count
	parameter	INC_STATE 	= 3'b010; //increment count
	parameter	INC2_STATE 	= 3'b011;
	parameter	DEC_STATE 	= 3'b100; //decrement count
	parameter	DEC2_STATE 	= 3'b101;
	
	input		[2:0]		state; //input
	input		[7:0]		d_in;
	output reg	[7:0]		d_out; //output
	
	wire		[7:0]		d_inc;
	wire		[7:0]		d_dec;
	
	always @ (state)
	begin
		case(state)
			IDLE_STATE 	:	d_out = 8'b0;
			LOAD_STATE 	:	d_out = d_in;
			INC_STATE 	:	d_out = d_inc;
			INC2_STATE 	:	d_out = d_inc;
			DEC_STATE 	:	d_out = d_dec;
			DEC2_STATE 	:	d_out = d_dec;
			default	  : d_out = 8'bx;
		endcase
	end

	cla8 U0_cla8(.a(d_out),.b(8'b00000001), .ci(1'b0), .s(d_inc)); // d_inc = d_in + 1
	cla8 U1_cla8(.a(d_out),.b(8'b11111111), .ci(1'b0), .s(d_dec)); // d_dec = d_in - 1

endmodule 


module cc_logic(op, shamt, d_in, d_out, do_next); // combinational circuit logic design
	input		[2:0]		op; //op code
	input		[1:0]		shamt; //shift amount
	input		[7:0]		d_in; //input
	input		[7:0]		d_out; // register's output
	output reg	[7:0]		do_next;	//output
	
	wire		[7:0]		d_lsl; 
	wire		[7:0]		d_lsr; 
	wire		[7:0]		d_asr; 
	
	parameter NOP = 3'b000; //no action
	parameter LOAD = 3'b001; //d_in = d_out
	parameter LSL = 3'b010; //Logical Shift Left
	parameter LSR = 3'b011; //Logical Shift Right
	parameter ASR = 3'b100; //Arthimetic Shift Right
	
	always @ (op, shamt, d_in, d_out, d_lsl, d_lsr, d_asr) 
	begin 
		case(op)
		
		NOP : 
		do_next <= d_out;
		
		LOAD :
		do_next <= d_in;

		LSL :
		do_next <= d_lsl;
		
		LSR :
		do_next <= d_lsr;
		
		ASR :
		do_next <= d_asr;
		
		default:
		do_next <= 8'bx;
		
		endcase
	end 
	
	//instance
	LSL8 U0_LSL8(d_in, shamt, d_lsl);
	LSR8 U1_LSR8(d_in, shamt, d_lsr);
	ASR8 U2_ASR8(d_in, shamt, d_asr);
	
endmodule 

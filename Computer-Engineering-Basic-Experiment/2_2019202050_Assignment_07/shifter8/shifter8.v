module shifter8(clk, reset, op, shamt, d_in, d_out); //8bit shifter design
	input clk, reset;
	input	[2:0]	op; //opcode
	input	[1:0]	shamt;//shift amount
	input	[7:0]	d_in;//input
	output [7:0] d_out; //output
	
	wire [7:0] next;
	
	cc_logic	U0_cc_logic(op,shamt,d_in,d_out,next); //cc_logic
	_register8_r U1_register8_r(clk,reset,next,d_out);//8bit register
	
endmodule 
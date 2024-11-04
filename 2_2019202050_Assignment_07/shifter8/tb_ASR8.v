`timescale 1ns/100ps
module tb_ASR8;//testbench for ASR8
	reg[7:0]	tb_d_in;
	reg[1:0]	tb_shamt;
	wire [7:0] tb_d_out;
	
	ASR8 U0_ASR8(tb_d_in,tb_shamt,tb_d_out);
	
	initial begin
	#5 tb_d_in = 8'b11100111; tb_shamt = 2'b00;
	#5 tb_d_in = 8'b11100111; tb_shamt = 2'b01;
	#5 tb_d_in = 8'b11100111; tb_shamt = 2'b10;
	#5 tb_d_in = 8'b11100111; tb_shamt = 2'b11;
	#5 tb_d_in = 8'b01100111; tb_shamt = 2'b00;
	#5 tb_d_in = 8'b01100111; tb_shamt = 2'b01;
	#5 tb_d_in = 8'b01100111; tb_shamt = 2'b10;
	#5 tb_d_in = 8'b01100111; tb_shamt = 2'b11;
	#5 $stop;
	end
endmodule
`timescale 1ns/100ps
module tb_cla32;
	reg [31:0] tb_a, tb_b;
	reg tb_ci;
	wire [31:0] tb_s;
	wire tb_co;
	wire [32:0] tb_result;	
	assign tb_result = {tb_co, tb_s}; //check carry at waveform

cla32 U0_cla32(tb_a,tb_b,tb_ci,tb_co,tb_s);//calling module

	initial begin
		tb_a = 32'h0000_0000; tb_b = 32'h0000_0000; tb_ci = 32'h0000_0000;
		#10; tb_a = 32'h4444_4444; tb_b = 32'h3333_3333; tb_ci = 1'b0;
		#10; tb_a = 32'h5555_5555; tb_b = 32'hbbbb_bbbb; tb_ci = 1'b0;
		#10; tb_a = 32'h8888_8888; tb_b = 32'h7777_7777; tb_ci = 1'b1;
		#10; tb_a = 32'h7425_7362; tb_b = 32'h8ac1_32f0; tb_ci = 1'b1;
		#10; tb_a = 32'hffff_ffff; tb_b = 32'hffff_ffff; tb_ci = 1'b0;
		#10; tb_a = 32'hffff_ffff; tb_b = 32'hffff_ffff; tb_ci = 1'b1;
		#10; $stop;
	end
endmodule

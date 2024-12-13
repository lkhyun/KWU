`timescale 1ns/100ps
module tb_dff_en; //testbench of dff_en
	reg tb_clk,tb_en,tb_d;//reg
	wire tb_q; //wire

	_dff_en U0_dff_en(tb_clk, tb_en, tb_d, tb_q); //instance of enable D ff
	
	always #5 tb_clk=~tb_clk; //set clock
	
	initial //test cases
	begin
		#0 tb_clk=0; tb_en=1; tb_d=0;
		#10 tb_d=1;
		#10 tb_d=0;
		#10 tb_d=1;
		#10 tb_d=0; tb_en=0;
		#10 tb_d=1;
		#10 tb_d=0;
		#10 tb_d=0; tb_en=1;
		#10 tb_d=1;
		#10 $stop;
	end
endmodule

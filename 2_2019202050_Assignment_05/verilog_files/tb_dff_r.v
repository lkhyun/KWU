`timescale 1ns/100ps
module tb_dff_r; //testbench of resettable d flip-flop
	reg tb_clk,tb_reset_n,tb_d; //input	
	wire tb_q; //output
	
	_dff_r U0_dff_r(tb_clk,tb_reset_n,tb_d,tb_q); //instance of resettable dff
	
	always #5 tb_clk=~tb_clk; //set clock
	
	initial
	begin //test cases
		#0 tb_clk=0; tb_reset_n=0; tb_d=0; //reset=0
		#3 tb_d=1;
		#10 tb_reset_n=1; tb_d=0; //reset=1
		#10 tb_d=1;
		#10 tb_d=0;
		#10 tb_d=1;
		#10 tb_d=0;
		#10 tb_reset_n=0;tb_d=1; //reset=0
		#10 tb_d=0;
		#10 tb_d=1;
		#10 $stop;
	end
endmodule

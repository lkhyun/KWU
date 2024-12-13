`timescale 1ns/100ps
module tb_dff;//testbench of dff
	wire tb_q ,tb_q_bar;//wire
	reg tb_clk ,tb_d; //register
	_dff U0_dff(.clk(tb_clk),.d(tb_d),.q(tb_q),.q_bar(tb_q_bar)); //instance of dlatch

	always #5 tb_clk=~tb_clk;//setting clock
	
	initial //test cases
	begin
		#0  tb_clk=0; tb_d=0;
		#10 tb_d=1;
		#10 tb_d=0;
		#10 tb_d=1;
		#10 tb_d=1;
		#10 tb_d=0;
		#10 $stop;
	end
endmodule

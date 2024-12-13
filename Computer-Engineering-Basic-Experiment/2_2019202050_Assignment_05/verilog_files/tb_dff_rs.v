`timescale 1ns/100ps
module tb_dff_rs;//testbench of dff_rs
	reg tb_clk,tb_set,tb_reset,tb_d;//reg
	wire tb_q;//wire
	
	_dff_rs U0_dff_rs(.clk(tb_clk),.set(tb_set),.reset(tb_reset),.d(tb_d),.q(tb_q)); //instance of _dff_rs
	always #5 tb_clk=~tb_clk;//setting clock
	initial
	begin
		#0 tb_clk=0; tb_set=0; tb_reset=0; tb_d=0; //reset=0, set=0
		#3 tb_d =1;
		#10 tb_d=0;
		#10 tb_d=1;
		#10 tb_d=0;
		#10 tb_d=1; tb_reset=1; //reset=1, set=0
		#10 tb_d=0;
		#10 tb_d=1;
		#10 tb_d=0;
		#10 tb_d=1; tb_set=1; //reset=1, set=1
		#10 tb_d=0;
		#10 tb_d=1;
		#10 tb_d=0;
		#10 $stop;
   end
endmodule 

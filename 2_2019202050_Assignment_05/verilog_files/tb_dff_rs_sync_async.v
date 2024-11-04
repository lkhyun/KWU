`timescale 1ns/100ps	//timescale
module tb_dff_rs_sync_async;
	reg tb_clk,tb_set_n,tb_reset_n,tb_d; //input
	wire tb_q_sync,tb_q_async; //output
	
	_dff_rs_sync_async U0_dff_rs_sync_async(.clk(tb_clk),.set(tb_set_n),.reset(tb_reset_n),.d(tb_d),.q_sync(tb_q_sync),.q_async(tb_q_async));
	
	always #5 tb_clk=~tb_clk; //setting clock
	always #3 tb_d=~tb_d;
	
	initial //test case
	begin
		tb_clk=0;tb_d=0;tb_set_n=0; tb_reset_n=0; tb_d=0;
		#10 tb_reset_n=1;
		#10 tb_reset_n=0;tb_set_n=1;
		#10 tb_reset_n=1;
		#10 tb_set_n=0;
		#10 tb_reset_n=0;
		#10 tb_set_n=1;
		#10 tb_reset_n = 0;
		#10 $stop;
	end
endmodule
 
	
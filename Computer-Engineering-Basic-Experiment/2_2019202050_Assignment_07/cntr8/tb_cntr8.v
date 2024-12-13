`timescale 1ns/100ps	
module tb_cntr8;	//cntr8 testbench

	reg tb_clk ,tb_reset_n ,tb_inc ,tb_load;	//input
	reg [7:0] tb_d_in;
	wire [7:0] tb_d_out; //output
	wire [2:0] tb_state;

	//cntr8 instance
	cntr8 U0_cntr8(tb_clk, tb_reset_n, tb_inc, tb_load, tb_d_in, tb_d_out, tb_state);

	always #5 tb_clk=~tb_clk;	//clock pulse

	initial
	begin
	#1 tb_clk=1'b0; tb_reset_n=1'b0; tb_inc=1'b0; tb_load=1'b0;	 tb_d_in = 8'b0;
	#7 tb_reset_n=1'b1; tb_inc=1'b1;
	#30 tb_inc = 1'b0;
	#10 tb_load = 1'b1; tb_inc=1'b1; tb_d_in=8'h0c;
	#10 tb_load = 1'b0; tb_d_in=8'h0F;
	#10 tb_inc = 1'b1;  tb_d_in = 8'b11001010; 
	#10 tb_inc = 1'b0;
	#10 tb_reset_n = 1'b0;
	#10 $stop;
	end
	
endmodule


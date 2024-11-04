`timescale 1ns/100ps

module tb_dlatch; //testbench of dlatch
	reg tb_clk,tb_d; //input
	wire tb_q,tb_q_bar; //output

	_dlatch U0_dlatch(tb_clk,tb_d,tb_q,tb_q_bar); //instance dlatch

	always #10 tb_clk = ~tb_clk; //setting clock

	initial begin
		tb_clk=0;
		tb_d=0;#10
		tb_d=1;#10 
		tb_d=0;#10
		tb_d=1;#10 
		tb_d=0;#10
		tb_d=0;#10 
		tb_d=1;#10
		$stop;
	end
endmodule
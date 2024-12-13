`timescale 1ns/100ps
module tb_register32;//testbench of 32 bits register
	reg tb_clk; //reg
	reg [31:0]tb_d;
	wire [31:0]tb_q; //wire

	_register32 U0_register32(.clk(tb_clk),.d(tb_d),.q(tb_q)); //instance of 32-bits register

	always //setting clock
	begin
		tb_clk=0; #25;
		tb_clk=1; #25;
	end

	initial //test cases
	begin 
		tb_d=32'h12345678;
		#15; tb_d=32'h98765432;
		#15; tb_d=32'hffeeddcc;
		#30; tb_d=32'hbbaa9876;
		#10; tb_d=32'h77665544;
		#20; tb_d=32'h33221100;
		#20; tb_d=32'h12345678;
		#30; $stop;
	end
endmodule 
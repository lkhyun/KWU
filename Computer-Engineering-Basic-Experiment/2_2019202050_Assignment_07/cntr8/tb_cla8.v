`timescale 1ns/100ps
module tb_cla8; //8bit carry look ahead Adder design
	reg [7:0] tb_a,tb_b; //input
	reg tb_ci;
	wire [7:0] tb_s; //output
	wire tb_co;
	
	cla8 tb_cla8(tb_a,tb_b,tb_ci,tb_co,tb_s);
	
	initial begin
		#5 tb_a = 8'b00000001; tb_b = 8'b00000000; tb_ci = 1'b0;
		#5 tb_a = 8'b00000001; tb_b = 8'b00000001;
		#5 tb_a = 8'b00000111; tb_b = 8'b00000101;
		#5 tb_a = 8'b11111111; tb_b = 8'b01011101;
		#5 tb_a = 8'b00000001; tb_b = 8'b00000000; tb_ci = 1'b1;
		#5 tb_a = 8'b00000001; tb_b = 8'b00000001;
		#5 tb_a = 8'b00000111; tb_b = 8'b00000101;
		#5 tb_a = 8'b11111111; tb_b = 8'b01011101;
		#5 $stop;
	end

endmodule

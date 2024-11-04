`timescale 1ns/100ps
module tb_mx4;//testbench for mx4 module
	reg [3:0]tb_d;
	reg [1:0]tb_s;
	wire tb_y;
	
	mx4 tb_mx4(tb_d[0],tb_d[1],tb_d[2],tb_d[3],tb_s,tb_y); //calling module
	
	initial begin
		#5 tb_d[0] = 1'b0; tb_d[1] = 1'b1; tb_d[2] = 1'b0; tb_d[3] = 1'b1; tb_s = 2'b00;
		#5 tb_s = 2'b01;
		#5 tb_s = 2'b10;
		#5 tb_s = 2'b11;
		#5 tb_d[0] = 1'b1; tb_d[1] = 1'b0; tb_d[2] = 1'b1; tb_d[3] = 1'b0; tb_s = 2'b00;
		#5 tb_s = 2'b01;
		#5 tb_s = 2'b10;
		#5 tb_s = 2'b11;
		#5 $stop;
	end
	
endmodule
		
		
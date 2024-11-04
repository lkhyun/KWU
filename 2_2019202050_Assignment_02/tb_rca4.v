`timescale 1ns/100ps //unit:1ns precision:100ps

module tb_rca4; // 4bits ripple carry adder design
		reg [3:0] tb_a,tb_b; //4 bits input
		reg tb_ci; //carry in
		wire tb_co;//carry out
		wire [3:0] tb_s; //4 bits sum
		wire [4:0] tb_result;// 5 bits results
		
		
		rca4 tb_rca(tb_a,tb_b,tb_ci,tb_co,tb_s);// calling rca4 module
		
		initial begin // Run once
				tb_a = 4'b0001; tb_b = 4'b0001; tb_ci = 0;
		#10;	tb_a = 4'b0010; tb_b = 4'b0001; tb_ci = 0;
		#10;	tb_a = 4'b0001; tb_b = 4'b0010; tb_ci = 0;
		#10;	tb_a = 4'b0111; tb_b = 4'b0001; tb_ci = 1;
		#10;	tb_a = 4'b0000; tb_b = 4'b0000; tb_ci = 1;
		#10;	tb_a = 4'b1111; tb_b = 4'b0111; tb_ci = 1;
		#10;	tb_a = 4'h9; tb_b = 4'h8; tb_ci = 0;
		#10;	tb_a = 4'h7; tb_b = 4'hf; tb_ci = 1;
		#10; // delay 10units
		end// test end
		//directed verification
		
		assign tb_result = {tb_co,tb_s}; // To view Carry out and Sums in a Bundle
	endmodule
	
		
				
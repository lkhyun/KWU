module register32_8(clk,reset_n,en,d_in,d_out0,d_out1,d_out2,d_out3,d_out4,d_out5,d_out6,d_out7);//8 32bits register
	input clk,reset_n;
	input [7:0] en; //enable
	input [31:0] d_in;
	output [31:0] d_out0,d_out1,d_out2,d_out3,d_out4,d_out5,d_out6,d_out7;
	
	register32_r_en U0_register_32_r_en(clk, reset_n,en[0],d_in,d_out0);
	register32_r_en U1_register_32_r_en(clk, reset_n,en[1],d_in,d_out1);
	register32_r_en U2_register_32_r_en(clk, reset_n,en[2],d_in,d_out2);
	register32_r_en U3_register_32_r_en(clk, reset_n,en[3],d_in,d_out3);
	register32_r_en U4_register_32_r_en(clk, reset_n,en[4],d_in,d_out4);
	register32_r_en U5_register_32_r_en(clk, reset_n,en[5],d_in,d_out5);
	register32_r_en U6_register_32_r_en(clk, reset_n,en[6],d_in,d_out6);
	register32_r_en U7_register_32_r_en(clk, reset_n,en[7],d_in,d_out7);
	//instance
	
endmodule
	
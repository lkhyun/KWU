module _register2_r_async(clk,reset_n,d,q);
	input clk,reset_n;
	input [1:0]d;
	output [1:0]q;
	
_dff_r_async U0_dff_r_async(clk,reset_n,d[0],q[0]);
_dff_r_async U1_dff_r_async(clk,reset_n,d[1],q[1]);
//instance with 2 async resettable dff
endmodule
	
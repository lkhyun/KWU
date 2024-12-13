module _register8_r(clk,reset,d,q);
	input clk,reset;
	input [7:0] d;
	output [7:0] q;
	
	_dff_r U0_dff_r(clk,reset,d[0],q[0]);
	_dff_r U1_dff_r(clk,reset,d[1],q[1]);
	_dff_r U2_dff_r(clk,reset,d[2],q[2]);
	_dff_r U3_dff_r(clk,reset,d[3],q[3]);
	_dff_r U4_dff_r(clk,reset,d[4],q[4]);
	_dff_r U5_dff_r(clk,reset,d[5],q[5]);
	_dff_r U6_dff_r(clk,reset,d[6],q[6]);
	_dff_r U7_dff_r(clk,reset,d[7],q[7]);
	//8 resettable dff instance
endmodule
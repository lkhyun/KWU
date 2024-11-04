module _register8(clk,d,q);
	input clk;
	input [7:0] d;
	output [7:0]q;
	
	_dff U0_dff(clk,d[0],q[0]);
	_dff U1_dff(clk,d[1],q[1]);
	_dff U2_dff(clk,d[2],q[2]);
	_dff U3_dff(clk,d[3],q[3]);
	_dff U4_dff(clk,d[4],q[4]);
	_dff U5_dff(clk,d[5],q[5]);
	_dff U6_dff(clk,d[6],q[6]);
	_dff U7_dff(clk,d[7],q[7]);
//8 d flip flop instance
endmodule
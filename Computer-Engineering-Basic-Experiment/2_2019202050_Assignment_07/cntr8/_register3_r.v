module _register3_r(clk, reset_n, d, q); //resettable 3bit register design
	input 				clk, reset_n; //input
	input		[2:0]		d;
	output	[2:0]		q; //output
	
	//resettable d flip-flop instance
	_dff_r	U0_dff_r(clk,reset_n,d[0],q[0]);
	_dff_r	U1_dff_r(clk,reset_n,d[1],q[1]);
	_dff_r	U2_dff_r(clk,reset_n,d[2],q[2]);

endmodule

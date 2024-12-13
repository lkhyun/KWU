module _dff_r(clk,reset,d,q);
	input clk,reset,d;
	output q;
	
	wire w_d;
	
	_and2 U0_and2(d,reset,w_d);//for reset implement
	_dff U1_dff(clk,w_d,q);
endmodule
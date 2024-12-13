module _dff_rs(clk,set,reset,d,q);
	input clk,set,reset,d;
	output q;
	
	wire w_d1,w_d2;
	
	_or2 U0_or2(d,~set,w_d1); //for active-low
	_and2 U1_and2(w_d1,reset,w_d2);
	_dff U2_dff(clk,w_d2,q);
endmodule
module _dff_en(clk,en,d,q);
	input clk,en,d;
	output q;
	
	wire w_d;
	
	mx2 U0_mx2(q,d,en,w_d);//Determine q and d by en
	_dff U1_dff(clk,w_d,q);
endmodule
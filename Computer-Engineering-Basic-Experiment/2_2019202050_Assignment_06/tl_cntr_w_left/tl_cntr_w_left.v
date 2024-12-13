module tl_cntr_w_left(clk,reset_n,Ta,Tal,Tb,Tbl,La,Lb);
	input clk,reset_n,Ta,Tal,Tb,Tbl;
	output [1:0]La,Lb;
	
	wire [2:0]d,q;
	
	ns_logic U0_ns_logic(d,Ta,Tal,Tb,Tbl,q);//register input = next state
	_register3_r U1_register3_r(clk,reset_n,d,q); //memory
	o_logic U3_o_logic(q,La,Lb);//register output = current state
	
endmodule
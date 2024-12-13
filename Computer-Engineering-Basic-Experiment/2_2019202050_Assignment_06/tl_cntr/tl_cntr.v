module tl_cntr(clk,reset_n,Ta,Tb,La,Lb);
	input clk,reset_n,Ta,Tb;
	output [1:0]La;
	output [1:0]Lb;
	wire [1:0]q,d;
	
	ns_logic U0_ns_logic(d,Ta,Tb,q);//register input = next state
	_register2_r_async U1_register2_r_async(clk,reset_n,d,q); //memory
	o_logic U3_o_logic(q,La,Lb);//register output = current state
	
endmodule

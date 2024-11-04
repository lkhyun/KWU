module o_logic(q,La,Lb);
	input [1:0]q;
	output [1:0]La;
	output [1:0]Lb;
	
	assign La[1] = q[1];
	_and2 U0_and2((~q[1]),q[0],La[0]);
	assign Lb[1] = ~q[1];
	_and2 U1_and2(q[1],q[0],Lb[0]);
	//traffic light instance
endmodule
	
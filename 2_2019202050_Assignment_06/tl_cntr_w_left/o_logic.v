module o_logic(q,La,Lb);
	input [2:0]q;
	output [1:0]La; //traffic light a
	output [1:0]Lb; //traffic light b
	
	wire w_a1,w_a2;
	
	_and2 U0_and2(q[1],(~q[0]),w_a1);//La[1] instance
	_or2 U1_or2(w_a1,q[2],La[1]);
	
	_or2 U2_or2(q[0],q[2],La[0]);//La[0] instance
	
	_and2 U3_and2(q[1],(~q[0]),w_a2);//Lb[1] instance
	_or2 U4_or2(w_a2,(~q[2]),Lb[1]);
	
	_or2 U5_or2((~q[2]),q[0],Lb[0]);//Lb[0] instance

endmodule
	
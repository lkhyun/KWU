module ns_logic(d,Ta,Tb,q);
	input [1:0] q;
	input Ta,Tb;
	output [1:0] d;
	wire w1,w2;
	
	_xor2 U0_xor2(q[1],q[0],d[1]);
	_and3 U1_and3((~q[1]),(~q[0]),(~Ta),w1);
	_and3 U2_and3(q[1],(~q[0]),(~Tb),w2);
	_or2 U3_or2(w1,w2,d[0]);
	//d instance
endmodule
	
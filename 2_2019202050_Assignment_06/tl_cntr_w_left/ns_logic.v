module ns_logic(d,Ta,Tal,Tb,Tbl,q);
	input [2:0] q;
	input Ta,Tal,Tb,Tbl;
	output [2:0] d;
	wire w0,w1,w2,w3,w4,w5,w6,w7;
	
	//d[2] instance
	_and3 U0_and3((~q[2]),q[1],q[0],w0);
	_and2 U1_and2(q[2],(~q[1]),w1);
	_and2 U2_and2(q[2],(~q[0]),w2);
	_or3 U3_or3(w0,w1,w2,d[2]);
	
	//d[1] instance
	_xor2 U4_xor2(q[1],q[0],d[1]);
	
	//d[0] instance
	_and3 U5_and3((~q[2]),(~q[1]),(~Ta),w3);
	_and3 U6_and3((~q[2]),q[1],(~Tal),w4);
	_and3 U7_and3(q[2],(~q[1]),(~Tb),w5);
	_and3 U8_and3(q[2],q[1],(~Tbl),w6);
	_or4 U9_or4(w3,w4,w5,w6,w7);
	_and2 U10_and2((~q[0]),w7,d[0]);
	
endmodule
	
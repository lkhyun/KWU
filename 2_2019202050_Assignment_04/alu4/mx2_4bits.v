module mx2_4bits(d0,d1,s,y); //4bits 2 to 1 mux design
	input [3:0] d0,d1;
	input s;
	output [3:0] y;
	
mx2 U0_mx2(d0[0],d1[0],s,y[0]);
mx2 U1_mx2(d0[1],d1[1],s,y[1]);
mx2 U2_mx2(d0[2],d1[2],s,y[2]);
mx2 U3_mx2(d0[3],d1[3],s,y[3]);
// 4 2to1 mux instance
endmodule


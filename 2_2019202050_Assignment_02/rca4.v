module rca4(a,b,ci,co,s); //4 bits ripple carry out module
	input [3:0] a,b; //4 bits input
	input ci; //carry in
	output co; //carry out
	output [3:0] s; //4 bits sums
	wire [2:0] c; //3 bits carry wire
	
fa U0_fa(a[0],b[0],ci,c[0],s[0]);
fa U1_fa(a[1],b[1],c[0],c[1],s[1]);
fa U2_fa(a[2],b[2],c[1],c[2],s[2]);
fa U3_fa(a[3],b[3],c[2],co,s[3]);
//connecting 4 fa modules

endmodule

module clb4(a,b,ci,c1,c2,c3,co);
	input [3:0]a,b; //4 bit input a,b
	input ci;
	output c1,c2,c3,co;
	wire [3:0]g,p; //4 bit input g,p
	wire w0_c1;
	wire w0_c2,w1_c2;
	wire w0_c3,w1_c3,w2_c3;
	wire w0_co,w1_co,w2_co,w3_co;
	//wire for c1~co instance implement

_and2 U0_and2(a[0],b[0],g[0]);
_and2 U1_and2(a[1],b[1],g[1]);
_and2 U2_and2(a[2],b[2],g[2]);
_and2 U3_and2(a[3],b[3],g[3]);
//generate instance

_or2 U0_or2(a[0],b[0],p[0]);
_or2 U1_or2(a[1],b[1],p[1]);
_or2 U2_or2(a[2],b[2],p[2]);
_or2 U3_or2(a[3],b[3],p[3]);
//Propagate instance

_and2 C1_and2(p[0],ci,w0_c1);
_or2 C1_or2(w0_c1,g[0],c1);
//c1 instance

_and3 C2_and3(p[0],p[1],ci,w0_c2);
_and2 C2_and2(p[1],g[0],w1_c2);
_or3 C2_or3(w0_c2,w1_c2,g[1],c2);
//c2 instance

_and4 C3_and4(p[0],p[1],p[2],ci,w0_c3);
_and3 C3_and3(p[1],p[2],g[0],w1_c3);
_and2 C3_and2(p[2],g[1],w2_c3);
_or4 C3_or4(w0_c3,w1_c3,w2_c3,g[2],c3);
//c3 instance

_and5 Co_and5(p[0],p[1],p[2],p[3],ci,w0_co);
_and4 Co_and4(p[1],p[2],p[3],g[0],w1_co);
_and3 Co_and3(p[2],p[3],g[1],w2_co);
_and2 Co_and2(p[3],g[2],w3_co);
_or5 Co_or5(w0_co,w1_co,w2_co,w3_co,g[3],co);
//co instance

endmodule

module mx8_4bits(a,b,c,d,e,f,g,h,s0,s1,s2,y); //4bits 8 to 1 mux design
	input [3:0] a,b,c,d,e,f,g,h;
	input s0,s1,s2;
	output [3:0] y;
	
mx8 U0_mx8(a[0],b[0],c[0],d[0],e[0],f[0],g[0],h[0],s0,s1,s2,y[0]);
mx8 U1_mx8(a[1],b[1],c[1],d[1],e[1],f[1],g[1],h[1],s0,s1,s2,y[1]);
mx8 U2_mx8(a[2],b[2],c[2],d[2],e[2],f[2],g[2],h[2],s0,s1,s2,y[2]);
mx8 U3_mx8(a[3],b[3],c[3],d[3],e[3],f[3],g[3],h[3],s0,s1,s2,y[3]);
//4 1bits 8to1 mux instance
endmodule

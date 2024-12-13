module mx16_32bits(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, s0, s1, s2, s3, y); //32bits 16to1 mux design
	input [31:0] a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;
	input	s0,s1,s2,s3;
	output [31:0] y;
	wire [31:0] w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13;


mx2_32bits U0_mx2_32bits(a,b,s0,w0);
mx2_32bits U1_mx2_32bits(c,d,s0,w1);
mx2_32bits U2_mx2_32bits(e,f,s0,w2);
mx2_32bits U3_mx2_32bits(g,h,s0,w3);
mx2_32bits U4_mx2_32bits(i,j,s0,w4);
mx2_32bits U5_mx2_32bits(k,l,s0,w5);
mx2_32bits U6_mx2_32bits(m,n,s0,w6);
mx2_32bits U7_mx2_32bits(o,p,s0,w7);

mx2_32bits U8_mx2_32bits(w0,w1,s1,w8);
mx2_32bits U9_mx2_32bits(w2,w3,s1,w9);
mx2_32bits U10_mx2_32bits(w4,w5,s1,w10);
mx2_32bits U11_mx2_32bits(w6,w7,s1,w11);

mx2_32bits U12_mx2_32bits(w8,w9,s2,w12);
mx2_32bits U13_mx2_32bits(w10,w11,s2,w13);

mx2_32bits U14_mx2_32bits(w12,w13,s3,y);

//15 mx2_32bits modules instance

endmodule

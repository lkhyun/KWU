module mx8_32bits(a, b, c, d, e, f, g, h, s0, s1, s2, y); //32bits 8to1 mux design
	input [31:0] a,b,c,d,e,f,g,h;
	input	s0,s1,s2;
	output [31:0] y;
	wire [31:0] w0, w1, w2, w3, w4, w5;


mx2_32bits U0_mx2_32bits(a,b,s0,w0);
mx2_32bits U1_mx2_32bits(c,d,s0,w1);
mx2_32bits U2_mx2_32bits(e,f,s0,w2);
mx2_32bits U3_mx2_32bits(g,h,s0,w3);
mx2_32bits U4_mx2_32bits(w0,w1,s1,w4);
mx2_32bits U5_mx2_32bits(w2,w3,s1,w5);
mx2_32bits U6_mx2_32bits(w4,w5,s2,y);
//7 mx2_32bits modules instance

endmodule

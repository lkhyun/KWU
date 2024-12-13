module mx2(d0,d1,s,y); // 2 to 1 mux design
	input d0,d1,s;
	output y;
	wire sb,w0,w1;
	
_inv U0_inv(s, sb);
_nand2 U1_nand2(d0, sb, w0);
_nand2 U2_nand2(d1, s, w1); 
_nand2 U3_nand2(w0, w1, y);
//1 inverter 3 2input nand instance
endmodule

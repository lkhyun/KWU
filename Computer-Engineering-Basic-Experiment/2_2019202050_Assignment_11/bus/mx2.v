module mx2(d0, d1, s, y); //1bits 2to1 mux design
	input d0, d1;
	input s;
	output y;
	
	assign y=(s==0)?d0:d1;//ternary operation
endmodule

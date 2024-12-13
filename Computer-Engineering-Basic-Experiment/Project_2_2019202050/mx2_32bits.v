module mx2_32bits(d0, d1, s, y); //32bits 2to1 mux design
	input [31:0] d0, d1;
	input s;
	output [31:0] y;
	
	assign y=(s==0)?d0:d1;//ternary operation
endmodule

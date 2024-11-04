module mx2_8bits(d0, d1, s, y); //8bits 2to1 mux design
	input [7:0] d0, d1;
	input s;
	output [7:0] y;
	
	assign y=(s==0)?d0:d1;//ternary operation
endmodule

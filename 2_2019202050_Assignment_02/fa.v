module fa(a,b,ci,co,s);// full adder design
	input a,b,ci;
	output co,s;
	wire c1,c2,sm;
	
ha fa_ha1(b,ci,c1,sm);
ha fa_ha2(a,sm,c2,s);
_or2 fa_or2(c2,c1,co);
//calling modules from gates.v

endmodule

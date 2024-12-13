module fa_v2(a,b,ci,s);// full adder design removed carryout
	input a,b,ci;
	output s;
	wire w0;
	
_xor2 xor2_1(b,ci,w0);
_xor2 xor2_2(a,w0,s);
//calling modules from gates.v

endmodule 

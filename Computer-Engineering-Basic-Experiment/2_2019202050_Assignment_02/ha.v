module ha(a,b,co,s); // half adder design
	input a,b;
	output co,s;
	
_and2 ha_co(a,b,co); //calling and2 logic from gate.v
_xor2 ha_s(a,b,s);   //calling xor2 logic from gate.v

endmodule

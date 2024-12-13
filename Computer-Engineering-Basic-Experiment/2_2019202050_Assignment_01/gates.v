`timescale 1ns/100ps //unit:1ns precision:100ps

module _nand2(a,b,y);//two-input nand gate module
	input a,b; 
	output y;
	assign y= ~(a & b); //nand logical operation
endmodule

module _inv(a,y);//inverter
	input a;
	output y;
	assign y= ~a;//not logic operation
	
endmodule 
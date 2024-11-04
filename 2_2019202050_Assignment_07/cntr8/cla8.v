module cla8(a, b, ci, co ,s); //8bit carry look ahead Adder design
	input [7:0] a,b; //input
	input ci;
	output [7:0] s; //output
	output co;
	
	wire c0;
	
	//4bit CLA instance
	cla4 U0_cla4(a[3:0],b[3:0],ci, c0, s[3:0]);
	cla4 U1_cla4(a[7:4],b[7:4],c0, co ,s[7:4]);

endmodule

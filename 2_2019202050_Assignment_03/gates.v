module _inv(a,y);// inverter design
	input a;
	output y;
	assign y=~a; //not logic
endmodule

module _nand2(a,b,y); // 2 input nand design
	input a,b;
	output y;
	assign y=~(a&b); //and, not logic
endmodule

module _and2(a,b,y);// 2 input and design
	input a,b;
	output y;
	assign y=a&b; //and logic
endmodule

module _or2(a,b,y);// 2 input or design
	input a,b;
	output y;
	assign y=a|b;//or logic
endmodule

module _xor2(a,b,y);// 2 input xor design
	input a,b;
	output y;
	wire w1,w2,inv_a,inv_b;

_inv inv0(a,inv_a);
_inv inv1(b,inv_b);
_and2 and2_a(inv_a,b,w1);
_and2 and2_b(a,inv_b,w2);
_or2 or2_y(w1,w2,y);
//calling logic gates
//This codes acts like an ^ operator

endmodule

module _and3(a,b,c,y);//3 input and design
	input a,b,c;
	output y;
	assign y=a&b&c;
endmodule

module _and4(a,b,c,d,y);//4 input and design
	input a,b,c,d;
	output y;
	assign y=a&b&c&d;
endmodule

module _and5(a,b,c,d,e,y);// 5 input and design
	input a,b,c,d,e;
	output y;
	assign y=a&b&c&d&e;
endmodule

module _or3(a,b,c,y); // 3 input or design
	input a,b,c; 
	output y; 
	assign y=a|b|c;
endmodule

module _or4(a,b,c,d,y); //4 input or design
	input a,b,c,d;
	output y;
	assign y=a|b|c|d;
endmodule

module _or5(a,b,c,d,e,y); //5 input or design
	input a,b,c,d,e;
	output y;
	assign y=a|b|c|d|e;
endmodule

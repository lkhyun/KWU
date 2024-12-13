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

module _inv_4bits(a,y); //4bits inverter design
input [3:0] a;
output [3:0] y;
assign y=~a;
endmodule

module _and2_4bits(a,b,y);//4bits 2input and design
input [3:0] a,b; 
output [3:0] y;
assign y=a&b;
endmodule

module _or2_4bits(a,b,y);//4bits 2input or design
input [3:0] a,b;
output [3:0] y;
assign y=a|b;
endmodule

module _xor2_4bits(a,b,y);//4 bits 2input xor design
input [3:0] a,b;
output [3:0] y;
_xor2 U0_xor2(.a(a[0]), .b(b[0]), .y(y[0]));
_xor2 U1_xor2(.a(a[1]), .b(b[1]), .y(y[1]));
_xor2 U2_xor2(.a(a[2]), .b(b[2]), .y(y[2])); 
_xor2 U3_xor2(.a(a[3]), .b(b[3]), .y(y[3]));
endmodule

module _xnor2_4bits(a,b,y);//4bits 2input xnor design
input[3:0] a,b;
output[3:0] y;
wire[3:0] w0;
_xor2_4bits U0_xor2_4bits(.a(a), .b(b), .y(w0));
_inv_4bits U1_inv_4bits(.a(w0), .y(y));
endmodule

module _inv_32bits(a,y);//32bits inverter design
input [31:0] a;
output [31:0] y;
assign y=~a;
endmodule

module _and2_32bits(a,b,y);//32bits 2input and design
input [31:0] a,b;
output [31:0] y;
assign y=a&b;
endmodule

module _or2_32bits(a,b,y);//32bits 2input or design
input [31:0] a,b;
output [31:0] y;
assign y=a|b;
endmodule

module _xor2_32bits(a, b, y);//32bits 2input xor design
input [31:0] a,b;
output [31:0] y;
_xor2_4bits U0_xor2_4bits(a[3:0],b[3:0],y[3:0]);
_xor2_4bits U1_xor2_4bits(a[7:4],b[7:4],y[7:4]);
_xor2_4bits U2_xor2_4bits(a[11:8],b[11:8],y[11:8]);
_xor2_4bits U3_xor2_4bits(a[15:12],b[15:12],y[15:12]);
_xor2_4bits U4_xor2_4bits(a[19:16],b[19:16],y[19:16]);
_xor2_4bits U5_xor2_4bits(a[23:20],b[23:20],y[23:20]);
_xor2_4bits U6_xor2_4bits(a[27:24],b[27:24],y[27:24]);
_xor2_4bits U7_xor2_4bits(a[31:28],b[31:28],y[31:28]);
endmodule

module _xnor2_32bits(a, b, y); //32bits 2input xnor design
input [31:0] a,b;
output [31:0] y;
_xnor2_4bits U0_xnor2_4bits(a[3:0],b[3:0],y[3:0]);
_xnor2_4bits U1_xnor2_4bits(a[7:4],b[7:4],y[7:4]);
_xnor2_4bits U2_xnor2_4bits(a[11:8],b[11:8],y[11:8]);
_xnor2_4bits U3_xnor2_4bits(a[15:12],b[15:12],y[15:12]);
_xnor2_4bits U4_xnor2_4bits(a[19:16],b[19:16],y[19:16]);
_xnor2_4bits U5_xnor2_4bits(a[23:20],b[23:20],y[23:20]);
_xnor2_4bits U6_xnor2_4bits(a[27:24],b[27:24],y[27:24]);
_xnor2_4bits U7_xnor2_4bits(a[31:28],b[31:28],y[31:28]);
endmodule

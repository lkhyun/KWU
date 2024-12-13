module alu32(a, b, op, result); //32bits arithmetic logic calculator design
	input [31:0] a, b;
	input [3:0] op;
	output [31:0] result;
	wire [31:0] w_add_b;
	wire [31:0] w_not_a, w_not_b, w_and, w_or, w_xor, w_xnor, w_less, w_greater, w_add, w_LSL, w_LSR, w_ASR; // result of each operation

_inv_32bits U0_inv_32bits (a, w_not_a);
_inv_32bits U1_inv_32bits (b, w_not_b);
_and2_32bits U2_and2_32bits (a,b, w_and);
_or2_32bits U3_or2_32bits (a,b, w_or);
_xor2_32bits U4_xor2_32bits (a,b,w_xor);
_xnor2_32bits U5_xnor2_32bits (a,b,w_xnor);

_lessthan U6_lessthan(a,b,w_less);
_greaterthan U7_greaterthan(a,b,w_greater);

LSL32 U8_LSL32(b,2'b01,w_LSL);
LSR32 U9_LSR32(b,2'b01,w_LSR);
ASR32 U10_ASR32(b,2'b01,w_ASR);

mx2_32bits U6_mx2_32bits (b,w_not_b, op[2], w_add_b); //add? sub?
cla32 U7_cla32_addsub (a,w_add_b, op[2], w_add);

mx16_32bits U8_mx16_32bits(w_not_a,w_not_b,w_and,w_or,w_xor,w_xnor, w_less, w_greater, w_LSL, w_LSR, w_ASR,w_add,w_add,32'bx,32'bx,32'bx,op[0],op[1],op[2],op[3],result);//results matching the command
//instance
endmodule

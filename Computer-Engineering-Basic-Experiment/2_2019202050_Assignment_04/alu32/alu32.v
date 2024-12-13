module alu32(a, b, op, result, c, n, z, v); //32bits arithmetic logic calculator design
	input [31:0] a, b;
	input [2:0] op;
	output [31:0] result;
	output c, n, z, v;
	wire [31:0] w_add_b;
	wire [31:0] w_not_a, w_not_b, w_and, w_or, w_xor, w_xnor, w_add; // result of each operation
	wire co_prev, co_add;

_inv_32bits U0_inv_32bits (a, w_not_a);
_inv_32bits U1_inv_32bits (b, w_not_b);
_and2_32bits U2_and2_32bits (a,b, w_and);
_or2_32bits U3_or2_32bits (a,b, w_or);
_xor2_32bits U4_xor2_32bits (a,b,w_xor);
_xnor2_32bits U5_xnor2_32bits (a,b,w_xnor);
mx2_32bits U6_mx2_32bits (b,w_not_b, op[0], w_add_b); //add? sub?
cla32_ov U7_cla32_addsub (a,w_add_b, op[0], co_add, co_prev,w_add);
mx8_32bits U8_mx8_32bits(w_not_a,w_not_b,w_and,w_or,w_xor,w_xnor,w_add,w_add,op[0],op[1],op[2],result);//results matching the command
cal_flags32 U9_cal_flags32(op, result,co_add,co_prev,c,n,z,v);//flag calculate
//instance
endmodule

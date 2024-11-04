module alu4(a, b, op, result, c, n, z, v); //arithmetic logic calculator design
input [3:0] a, b;
input [2:0] op;
output [3:0] result;
output c, n, z, v;
wire [3:0] w_add_b; 
wire [3:0] w_not_a,w_not_b, w_and, w_or, w_xor, w_xnor, w_add; // result of each operation
wire c3_add, co_add; //top 2 bits

_inv_4bits U0_inv_4bits (a, w_not_a);
_inv_4bits U1_inv_4bits (b, w_not_b);
_and2_4bits U2_and2_4bits (a, b, w_and);
_or2_4bits U3_or2_4bits (a, b, w_or);
_xor2_4bits U4_xor2_4bits (a, b, w_xor);
_xnor2_4bits U5_xnor2_4bits (a, b, w_xnor);

mx2_4bits U6_mx2_4bits (b, w_not_b, op[0], w_add_b); //add? sub?
cla4_ov U7_addsub (a, w_add_b, op[0], co_add, c3_add ,w_add); 
mx8_4bits U7_mx8_4bits (w_not_a, w_not_b, w_and, w_or, w_xor, w_xnor, w_add, w_add, op[0], op[1],op[2],result); //results matching the command
cal_flags4 U8_cal_flags4 (op, result, co_add, c3_add, c, n, z, v); //flag calculate
//instance
endmodule
 



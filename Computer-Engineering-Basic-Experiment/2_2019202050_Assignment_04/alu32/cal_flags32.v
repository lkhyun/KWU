module cal_flags32(op, result, co_add, co_prev_add, c, n, z, v); //32bits flag calculate
input [2:0] op; //opcode
input co_add,co_prev_add;//top 2 carryout
input [31:0] result;
output c, n, z, v; //flag

assign c = (op[2:1] != 2'b11) ? 1'b0 : co_add; //carryout when opcode 11?, co is c
assign n = result[31]; //negative
assign z = (result == 32'b0) ? 1'b1 : 1'b0; //zero
assign v = (op[2:1] != 2'b11) ? 1'b0 : co_add ^ co_prev_add; // top 2bits xor calculate

endmodule

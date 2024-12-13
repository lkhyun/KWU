module cal_flags4(op, result, co, c3, c, n, z, v); // flag calculator design
	input [2:0] op; //opcode
	input [3:0] result;
	input co, c3;
	output c, n, z, v; //flag
	assign c = (op[2:1] != 2'b11) ? 1'b0 : co; //carryout when opcode 11?, co is c
	assign n = result[3]; //MSB
	assign z = (result == 4'b0) ? 1'b1 : 1'b0; //zero
	assign v = (op[2:1] != 2'b11) ? 1'b0 : co ^ c3; // top 2bits xor calculate
endmodule 
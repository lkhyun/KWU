`timescale 1ns/100ps
module tb_alu32;
	reg [31:0] a, b;
	reg [3:0] op;
	wire [31:0] result;
	
	alu32 U0_alu32(a, b, op, result);
	
	initial begin
		
		#10 a = 32'h0000000A; b = 32'hC000000B; op = 4'b0000;//not A
		#10 op = 4'b0001;//not B
		#10 op = 4'b0010;//and
		#10 op = 4'b0011;//or
		#10 op = 4'b0100;//xor
		#10 op = 4'b0101;//xnor
		#10 op = 4'b0110;//set less than
		#10 op = 4'b0111;//set greater than
		#10 op = 4'b1000;//LSL
		#10 op = 4'b1001;//LSR
		#10 op = 4'b1010;//ASR
		#10 op = 4'b1011;//addition
		#10 op = 4'b1100;//subtraction
		#10 op = 4'b1101;//exception
		#10 op = 4'b1110;//exception
		#10 op = 4'b1111;//exception
		#10 $stop;
	end
endmodule
`timescale 1ns/100ps
module tb_multiplier;
	reg clk,reset_n,op_start,op_clear;
	reg [63:0] multiplier,multiplicand;
	wire op_done;
	wire [127:0] result;
	
	multiplier U0_multiplier(clk,reset_n,multiplier,multiplicand,op_start,op_clear,op_done,result); //calling module
	
	always #5 clk = ~clk; //clock setting
	
	initial begin
		#7 clk = 0; reset_n = 0;
		#10 reset_n = 1; op_start = 1; op_clear = 0; multiplier = 64'h00000000_00000017; multiplicand = 64'h00000000_00000568;
		#10 op_start = 0; 
		#350 op_clear = 1;
		#10 op_start = 1; op_clear = 0; multiplier = 64'h00000000_00990767; multiplicand = 64'hf0000000_00006808;
		#10 op_start = 0; 
		#100 op_clear = 1;
		#10 $stop;
	end
	
endmodule

`timescale 1ns/100ps
module tb_multiplier;
	reg clk,reset_n,op_start,op_clear;
	reg [31:0] multiplier,multiplicand;
	wire op_done;
	wire [63:0] result;
	
	multiplier U0_multiplier(clk,reset_n,multiplier,multiplicand,op_start,op_clear,op_done,result); //calling module
	
	always #5 clk = ~clk; //clock setting
	
	initial begin
		#7 clk = 0; reset_n = 0;
		#10 reset_n = 1; op_start = 1; op_clear = 0; multiplier = 32'h0000_0017; multiplicand = 32'h0000_0568;
		#10 op_start = 0; 
		#350 op_clear = 1;
		#10 op_start = 1; op_clear = 0; multiplier = 32'h0000_0767; multiplicand = 32'hf000_6808;
		#10 op_start = 0; 
		#350 op_clear = 1;
		#10 $stop;
	end
	
endmodule

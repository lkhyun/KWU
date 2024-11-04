`timescale 1ns/100ps
module tb_rca_clk; 

	reg clk;
	reg [31:0] tb_a, tb_b;
	reg tb_ci;
	wire [31:0] tb_s_rca;
	wire tb_co_rca;
	wire [32:0] tb_result;
	assign tb_result = {tb_co_rca, tb_s_rca};
	
	parameter STEP = 10; //setting parameter
	
	rca_clk U0_rca_clk(clk, tb_a, tb_b, tb_ci, tb_co_rca, tb_s_rca); //rca_clk module calling
	
	always #(STEP/2) clk = ~clk; // implement clock
		initial begin
				clk = 1'b1; tb_a = 32'h0000_0000; tb_b = 32'h0000_0000; tb_ci = 1'b0;
			#(STEP-2); tb_a = 32'hffff_ffff; tb_b = 32'h0000_0000; tb_ci = 1'b1;
			#(STEP); tb_a = 32'h0000_ffff; tb_b = 32'hffff_0000; tb_ci = 1'b0;
			#(STEP); tb_a = 32'h135f_a562; tb_b = 32'h3561_4642; tb_ci = 1'b0;
			#(STEP*2); $stop; 
		end
endmodule
`timescale 1ns/100ps
module tb_ram;
	reg clk, cen, wen;
	reg [4:0] S_addr;
	reg [31:0] S_din;
	wire [31:0] S_dout;
	
	ram tb_ram(clk, cen, wen, S_addr, S_din, S_dout);
	
	always #5 clk = ~clk;
	
	initial begin
		#7 clk = 1'b1; cen = 1'b0; wen = 1'b0; S_addr = 5'b00010; S_din = 32'h00000007;
		#10 wen = 1'b1;
		#10 cen = 1'b1; wen = 1'b1; S_addr = 5'b00011; S_din = 32'h00000005;
		#10 wen = 1'b0; S_addr = 5'b00010;
		#10 S_addr = 5'b00011;
		#10 $stop;
	end
endmodule
`timescale 1ns/100ps
module tb_ram;
	reg clk, cen, wen;
	reg [4:0] addr;
	reg [31:0] din;
	wire [31:0] dout;
	
	ram U0_ram(clk,cen,wen,addr,din,dout); //calling module
	
	always #5 clk = ~clk;
	
	initial begin
		#7 clk = 0; cen = 0; wen = 0; addr = 5'b00011; din = 32'h00000005;
		#10 cen = 1; wen = 0;
		#10 cen = 1; wen = 1;
		#10 cen = 1; wen = 0;
		#10 cen = 1; wen = 1; addr = 5'b00110; din = 32'h00000007;
		#10 cen = 1; wen = 0;
		#30 $stop;
	end
endmodule
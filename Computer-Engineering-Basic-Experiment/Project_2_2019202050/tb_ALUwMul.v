`timescale 1ns/100ps
module tb_ALUwMul;
	reg clk, reset_n, S_sel,S_wr;
	reg [7:0] S_addr;
	reg [31:0] S_din;
	wire [31:0] S_dout;
	
	ALUwMul U0_ALUwMul(clk, reset_n, S_sel, S_wr, S_addr, S_din, S_dout);
	
	always #5 clk = ~clk;
	
	initial begin
		#7 clk = 1'b0; reset_n = 1'b0;
		#20 reset_n = 1'b1;S_sel =1'b0; S_wr = 1'b1; S_addr = 8'h00; S_din = 32'h00000005;
		#20 S_addr = 8'h01; S_din = 32'h00000007;
		#20 S_addr = 8'h02; S_din = 32'h0000000B;
		#20 S_addr = 8'h03; S_din = 32'h00000001;
		#20 S_wr = 1'b0; S_addr = 8'h04; 
		#20 
		#20 S_addr = 8'h06;
		#20 S_wr = 1'b1; S_sel = 1'b1; S_addr = 8'h05; S_din = 32'h00000001;
		#20 S_addr = 8'h00; S_din = 32'h00000003;
		#20 S_addr = 8'h01; S_din = 32'h00000009;
		#20 S_addr = 8'h02; S_din = 32'h0000000C;
		#20 S_addr = 8'h03; S_din = 32'h00000001;
		#20 S_wr = 1'b0; S_addr = 8'h04; 
		#20 
		#20 S_addr = 8'h06;
		#20 S_wr = 1'b1; S_addr = 8'h05; S_din = 32'h00000001;
		#20 S_addr = 8'h00; S_din = 32'h00000004;
		#20 S_addr = 8'h01; S_din = 32'h00000008;
		#20 S_addr = 8'h02; S_din = 32'h0000000D;
		#20 S_addr = 8'h03; S_din = 32'h00000001;
		#20 S_wr = 1'b0; S_addr = 8'h04; 
		#20 
		#300
		#20 S_addr = 8'h06;
		#20 S_addr = 8'h07;
		#20
		#20 S_wr = 1'b1; S_addr = 8'h00; S_din = 32'h00000005;
		#20 S_addr = 8'h01; S_din = 32'h00000003;
		#20 S_addr = 8'h02; S_din = 32'h0000000A;
		#20 S_addr = 8'h03; S_din = 32'h00000001;
		#20
		#20 S_wr = 1'b0; S_addr = 8'h04; 
		#20 S_addr = 8'h00;
		#20 S_addr = 8'h01;
		#20 S_addr = 8'h02;
		#20 S_addr = 8'h03;
		#20 S_addr = 8'h06;
		#20 S_addr = 8'h07;
		#20
		#20 S_wr = 1'b1; S_addr = 8'h04; S_din = 32'h0;
		#20 S_addr = 8'h00; S_din = 32'h00000005;
		#20 S_addr = 8'h01; S_din = 32'h0000000A;
		#20 S_addr = 8'h02; S_din = 32'h0000000D;
		#20 S_addr = 8'h03; S_din = 32'h00000001;
		#20 S_wr = 1'b0; S_addr = 8'h04; 
		#320
		#20 S_addr = 8'h06;
		#20 S_addr = 8'h07;
		#20 $stop;
	end
	
endmodule
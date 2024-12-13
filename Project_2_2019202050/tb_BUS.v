`timescale 1ns/100ps
module tb_BUS;
	reg clk, reset_n, M_req, M_wr;
	reg [7:0] M_addr;
	reg [31:0] M_dout, S0_dout, S1_dout;
	wire M_grant, S0_sel, S1_sel;
	wire S_wr;
	wire[7:0] S_addr;
	wire[31:0] M_din;
	wire[31:0] S_din;
	
	BUS U0_BUS(clk, reset_n, M_req, M_wr, M_addr, M_dout, S0_dout, S1_dout, M_grant, M_din, S0_sel, S1_sel, S_addr, S_wr, S_din);
	
	always #5 clk = ~clk;
	
	initial begin
		#7 clk = 1'b0; reset_n = 1'b0; M_req =1'b0; M_wr = 1'b0; M_addr = 8'h00; M_dout = 32'h0; S0_dout = 32'h0; S1_dout = 32'h0;
		#10 reset_n = 1'b1; M_wr = 1'b1; M_addr = 8'h03; M_dout = 32'h00000005; S0_dout = 32'h00000007; S1_dout = 32'h00000009;
		#10 M_req = 1'b1;
		#10 M_addr = 8'h31;
		#20 $stop;
	end
endmodule
		
module BUS(clk, reset_n, M_req, M_wr, M_addr, M_dout, S0_dout, S1_dout, M_grant, M_din, S0_sel, S1_sel, S_addr, S_wr, S_din);
	input clk, reset_n, M_req, M_wr;
	input [7:0] M_addr;
	input [31:0] M_dout, S0_dout, S1_dout;
	output M_grant, S0_sel, S1_sel;
	output reg S_wr;
	output reg[7:0] S_addr;
	output [31:0] M_din;
	output reg[31:0] S_din;
	wire slavesel0,slavesel1;
	
	register1 U0_register1(clk, reset_n, M_req, M_grant); //arbiter
	BUS_addr U1_BUS_addr(S_addr, S0_sel, S1_sel);
	register1 U2_register1(clk, reset_n, S0_sel,slavesel0);
	register1 U3_register1(clk, reset_n, S1_sel,slavesel1);
	mx3_32bits U4_mx3_32bits(32'h00, S0_dout, S1_dout, slavesel0, slavesel1, M_din);
	
	always@(M_grant or M_addr or M_wr or M_dout) begin //if grant is 1, assign value
		if(M_grant == 1) begin
			S_addr = M_addr;
			S_wr = M_wr;
			S_din = M_dout;
		end
		else begin
			S_addr = 8'b0;
			S_wr = 1'b0;
			S_din = 32'b0;
		end
	end
endmodule
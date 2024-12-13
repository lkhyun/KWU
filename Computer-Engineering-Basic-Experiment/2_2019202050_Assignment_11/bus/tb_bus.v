`timescale 1ns/100ps
module tb_bus;
	reg clk,reset_n,m0_req,m0_wr,m1_req,m1_wr;
	reg [7:0] m0_address,m1_address;
	reg [31:0] m0_dout,m1_dout,s0_dout,s1_dout;
	wire m0_grant,m1_grant,s0_sel,s1_sel,s_wr;
	wire [7:0] s_address;
	wire [31:0] m_din,s_din;
	
	bus tb_bus(clk,reset_n,m0_req,m0_wr,m0_address,m0_dout,m1_req,m1_wr,m1_address,m1_dout,s0_dout,s1_dout,m0_grant,m1_grant,m_din,s0_sel,s1_sel,s_address,s_wr,s_din);
	
	always #5 clk = ~clk;
	
	initial begin
	clk = 1'b0; reset_n=1'b0; m0_address=8'b0; m1_address=8'b0; m0_dout =32'b0; m1_dout=32'b0; m0_req=1'b0; m0_wr=1'b0; m1_req=1'b0; m1_wr=1'b0; s0_dout =32'b0; s1_dout=32'b0;
	#7; reset_n = 1'b1;
	#10; m0_req = 1'b1; m1_req = 1'b1; //m0 has property
	#10; s0_dout = 32'h1; s1_dout = 32'h2;	
	#10; m0_wr = 1'b1; m1_req = 1'b0;
	#10; m0_address = 8'h01; m0_dout = 32'h2;//sel0
	#10; m0_address = 8'h02; m0_dout = 32'h4;//sel0
	#10; m0_address = 8'h20; m0_dout = 32'h20; //sel1
	#10; m0_address = 8'h21; m0_dout = 32'h22; //sel1
	#10; m0_address = 8'ha0; m0_dout = 32'hff;// no sel
	#10; m0_req = 1'b0; m1_req = 1'b1;//m1_grant
	#10; m0_req = 1'b1; m1_req = 1'b1;//m1_grant
	#10; m0_req = 1'b1; m1_req = 1'b0;//m0_grant
	#20; $stop;
	end
endmodule
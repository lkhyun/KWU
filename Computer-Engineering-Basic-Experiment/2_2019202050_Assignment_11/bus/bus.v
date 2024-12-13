module bus(clk,reset_n,m0_req,m0_wr,m0_address,m0_dout,m1_req,m1_wr,m1_address,m1_dout,s0_dout,s1_dout,m0_grant,m1_grant,m_din,s0_sel,s1_sel,s_address,s_wr,s_din);
	input clk,reset_n,m0_req,m0_wr,m1_req,m1_wr;
	input [7:0] m0_address,m1_address;
	input [31:0] m0_dout,m1_dout,s0_dout,s1_dout;
	output m0_grant,m1_grant,s0_sel,s1_sel,s_wr;
	output [7:0] s_address;
	output [31:0] m_din,s_din;
	wire [1:0] arbitsel;
	wire [1:0] doutsel;
	
	bus_arbit U0_bus_arbit(m0_req,m1_req,reset_n,clk,arbitsel);//who requested?
	
	mx2 U1_mx2(m0_wr,m1_wr,arbitsel[0],s_wr);//Where to write where requested
	mx2_8bits U2_mx2_8bits(m0_address,m1_address,arbitsel[0],s_address);//address where requested
	mx2_32bits U3_mx2_32bits(m0_dout,m1_dout,arbitsel[0],s_din);//data where requested
	
	bus_addr U4_bus_addr(s_address,s0_sel,s1_sel);//address decord
	
	register2 U5_register2(clk,reset_n,{s0_sel,s1_sel},doutsel);//for mux clock synchronization
	
	mx3_32bits U6_mx3_32bits(32'h00,s0_dout,s1_dout,doutsel,m_din);
	
	assign m0_grant = arbitsel[1];
	assign m1_grant = arbitsel[0];

endmodule
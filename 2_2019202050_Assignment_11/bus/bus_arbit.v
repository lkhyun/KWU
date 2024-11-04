module bus_arbit(m0_req,m1_req,reset_n,clk,sel);//who requested
	input m0_req,m1_req,reset_n,clk;
	output [1:0]sel;
	reg [1:0] nextstate,curstate;
	parameter m0_grant = 2'b10; //m0_grant == 1, m1_grant == 0
	parameter m1_grant = 2'b01; //m0_grant == 0, m1_grant == 1
	
	always@(posedge clk or negedge reset_n) begin
		if(reset_n == 1'b0)
			curstate <= m0_grant;
		else
			curstate <= nextstate;
	end
	
	always@(m0_req or m1_req or curstate) begin
		case({m0_req,m1_req,curstate})
			{1'b0,1'b0,m0_grant}: nextstate <= m0_grant;
			{1'b0,1'b0,m1_grant}: nextstate <= m0_grant;
			{1'b0,1'b1,m0_grant}: nextstate <= m1_grant;
			{1'b0,1'b1,m1_grant}: nextstate <= m1_grant;
			{1'b1,1'b0,m0_grant}: nextstate <= m0_grant;
			{1'b1,1'b0,m1_grant}: nextstate <= m0_grant;
			{1'b1,1'b1,m0_grant}: nextstate <= m0_grant;
			{1'b1,1'b1,m1_grant}: nextstate <= m1_grant;
			default: nextstate <= 2'bx;
		endcase
	end
	assign sel = curstate; //reflect current status
endmodule
			
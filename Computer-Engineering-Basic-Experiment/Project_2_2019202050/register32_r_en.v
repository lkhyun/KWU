module register32_r_en(clk,reset_n,en,d,q);//32bit enable resettable register
	input clk,reset_n, en;
	input [31:0] d;
	output reg [31:0]q;
	
	always@(posedge clk or negedge reset_n) begin
		if(reset_n == 0)
			q <= 32'b0;
		else if(en == 1)
			q <= d;
		else
			q <= q; //default
	end
endmodule

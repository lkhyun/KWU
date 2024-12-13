module register2(clk,reset_n,d,q);
	input clk,reset_n;
	input [1:0] d;
	output reg [1:0] q;
	
	always@(posedge clk or negedge reset_n) begin
		if(reset_n == 1'b0)
			q <= 2'b00;
		else
			q <= d;
	end
endmodule
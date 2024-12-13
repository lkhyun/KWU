module register1(clk, reset_n, d, q);
	input clk, reset_n;
	input d;
	output reg q;
	
	always@(posedge clk or negedge reset_n) begin
		if(reset_n == 1'b0)
			q <= 1'b0;
		else
			q <= d;
	end
endmodule
module register3_r(clk,reset_n,d,q);//3bit resettable register
	input clk,reset_n;
	input [2:0] d;
	output reg [2:0]q;
	
	always@(posedge clk or negedge reset_n) begin
		if(reset_n == 0)
			q <= 3'b0;
		else
			q <= d; //default
	end
endmodule

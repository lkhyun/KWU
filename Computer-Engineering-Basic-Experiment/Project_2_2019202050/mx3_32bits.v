module mx3_32bits(d0, d1, d2, s0,s1, y); //32bits 3to1 mux design
	input [31:0] d0, d1, d2;
	input s0,s1;
	output reg [31:0] y;
	
	always@(d0,d1,d2,s0,s1) begin
		if(s0 == 1'b0 && s1 == 1'b0)
			y <= d0;
		else if(s0 == 1'b1 && s1 == 1'b0)
			y <= d1;
		else if(s0 == 1'b0 && s1 == 1'b1)
			y <= d2;
		else
			y <= 32'bx;
	end
endmodule

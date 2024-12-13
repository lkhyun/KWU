module mx3_32bits(d0, d1, d2, s, y); //32bits 3to1 mux design
	input [31:0] d0, d1, d2;
	input [1:0] s;
	output reg [31:0] y;
	
	always@(d0,d1,d2,s) begin
		case(s)
			2'b00: y <= d0;
			2'b10: y <= d1;
			2'b01: y <= d2;
			default: y <= 2'bx;
		endcase
	end
endmodule

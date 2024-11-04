module rca_clk(clk,a,b,ci,co,s);
	input [31:0] a,b;
	input clk,ci;
	output co;
	output [31:0] s;
	
	reg [31:0] reg_a,reg_b,reg_s;
	reg reg_ci,reg_co;
	
	wire [31:0] wire_s; 
	wire wire_co;
	
	rca32 U0_rca32(reg_a,reg_b,reg_ci,wire_co,wire_s);
	assign co = reg_co;
	assign s = reg_s;
	
	always @ (posedge clk) begin //Simultaneous allocation
	reg_a <= a;
	reg_b <= b;
	reg_ci <= ci;
	reg_co <= wire_co;
	reg_s <= wire_s;
	end

endmodule
	
	
	
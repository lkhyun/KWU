module cla_clk(clk,a,b,ci,co,s);
	input clk,ci;
	input [31:0] a,b;
	output co;
	output [31:0] s;
	
	reg [31:0] reg_a,reg_b,reg_s;
	reg reg_ci,reg_co;
	
	wire [31:0] wire_s;
	wire wire_co;
	
	cla32 U0_cla32(reg_a, reg_b, reg_ci, wire_co, wire_s); //calling module
	assign s = reg_s; 
	assign co = reg_co;
	
	always @ (posedge clk) begin //Simultaneous allocation
	reg_a <= a;
	reg_b <= b;
	reg_ci <= ci;
	reg_s <= wire_s;
	reg_co <= wire_co;
	end

endmodule


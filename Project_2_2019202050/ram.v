module ram(clk, cen, wen, S_addr, S_din, S_dout);
	input clk, cen, wen;
	input [4:0] S_addr;
	input [31:0] S_din;
	output reg [31:0] S_dout;
	
	reg [31:0] memory[0:31];
	integer i;
	
	initial begin
		for(i=0; i<32; i=i+1)
			memory[i] <= 32'b0; //memory initializing
	end
	
	always@(posedge clk) begin
		if(cen == 1'b0)
			S_dout <= 32'b0;
		else if(cen == 1'b1 && wen == 1'b0)
			S_dout <= memory[S_addr];
		else if(cen == 1'b1 && wen == 1'b1) begin
			memory[S_addr] <= S_din;
			S_dout <= 32'b0;
		end
		else
			S_dout <= 32'b0;
	end
endmodule
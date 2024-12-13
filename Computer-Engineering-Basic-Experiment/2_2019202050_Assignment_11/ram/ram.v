module ram(clk,cen,wen,addr,din,dout);
	input clk, cen, wen;
	input [4:0] addr;
	input [31:0] din;
	output reg [31:0] dout;
	
	reg [31:0] mem [0:31];//memory declare
	integer i; //loop variable
	
	initial begin //memory initialize
		for(i = 0; i<32;i = i+1)
			mem[i] <= 32'b0;
	end
	
	always@(posedge clk) begin
		case({cen,wen})
			{1'b0,1'b0}: dout <= 32'b0;
			{1'b0,1'b1}: dout <= 32'b0;
			{1'b1,1'b0}: dout <= mem[addr]; //read
			{1'b1,1'b1}: begin//write
				mem[addr] <= din;
				dout <= 32'b0;
			end
			default: dout <= 32'bx;
		endcase
	end
endmodule
`timescale 1ns/100ps//set timescale

module tb_Register_file;

	reg tb_clk,tb_reset_n,tb_we;
	reg [2:0]tb_wAddr,tb_rAddr;
	reg [31:0]tb_wData;

	wire [31:0]tb_rData;
	
	//register file instance
	Register_file U0_Register_file(tb_clk,tb_reset_n,tb_we,tb_wAddr,tb_rAddr,tb_wData,tb_rData);

	always #5 tb_clk = ~tb_clk;//clock pulse

	initial begin
	tb_clk = 0;  tb_reset_n=0; tb_we=0; tb_wData=32'h00000000; tb_rAddr=3'b000; tb_wAddr=3'b000; //initializing
	#8 tb_reset_n=1; tb_we=1;
	#10 tb_wAddr=3'b000; tb_wData=32'h0043adff; 
	#10 tb_wAddr=3'b010; tb_wData=32'h23456789;
	#10 tb_wAddr=3'b100; tb_wData=32'h11111111;
	#10 tb_wAddr=3'b111; tb_wData=32'hffffffff;
	#10 tb_we=0;
	#10 tb_rAddr=3'b000;
	#10 tb_rAddr=3'b010;
	#10 tb_rAddr=3'b100;
	#10 tb_rAddr=3'b111;
	#10 tb_reset_n=0;
	#10 $stop;
	end
endmodule

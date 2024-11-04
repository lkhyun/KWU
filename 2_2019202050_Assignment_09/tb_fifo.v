`timescale 100ns/1ps //time unit setting
module tb_fifo;
	reg tb_clk,tb_reset_n,tb_rd_en,tb_wr_en;
	reg [31:0] tb_d_in;
	wire [31:0] tb_d_out;
	wire tb_full,tb_empty,tb_wr_ack,tb_wr_err,tb_rd_ack,tb_rd_err; //flag
	wire [3:0]tb_data_count;
	
	fifo U0_fifo(tb_clk, tb_reset_n, tb_rd_en, tb_wr_en,tb_d_in,tb_d_out,tb_full,tb_empty,tb_wr_ack,tb_wr_err,tb_rd_ack,tb_rd_err,tb_data_count); //calling module
	
	always #5 tb_clk = ~tb_clk; //clock pulse
	
	initial begin
		#7 tb_clk = 0; tb_reset_n = 0; tb_rd_en = 0; tb_wr_en = 0;
		#10 tb_reset_n = 1; tb_rd_en = 0; tb_wr_en = 0; tb_d_in = 32'h11111111;
		#10 tb_rd_en = 1; tb_wr_en = 0; 
		#10 tb_rd_en = 0; tb_wr_en = 1; 
		#10 tb_rd_en = 0; tb_wr_en = 1; tb_d_in = 32'h22222222;
		#10 tb_d_in = 32'h33333333;
		#10 tb_d_in = 32'h44444444;
		#10 tb_d_in = 32'h55555555;
		#10 tb_d_in = 32'h66666666;
		#10 tb_d_in = 32'h77777777;
		#10 tb_d_in = 32'h88888888;
		#10 tb_d_in = 32'h99999999;
		#10 tb_rd_en = 1; tb_wr_en = 0;
		#90 tb_reset_n = 0;
		#10 $stop;
	end
endmodule
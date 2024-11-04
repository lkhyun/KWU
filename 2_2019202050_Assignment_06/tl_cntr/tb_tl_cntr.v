`timescale 1ns/100ps
module tb_tl_cntr;
	reg tb_clk,tb_reset_n,tb_Ta,tb_Tb;
	wire [1:0]tb_La,tb_Lb;
	
	tl_cntr U0_tl_cntr(tb_clk,tb_reset_n,tb_Ta,tb_Tb,tb_La,tb_Lb);//calling controler module
	always #5 tb_clk = ~tb_clk; //clock pulse
	
	initial	
	begin //test cases
		#0 tb_clk=1'b0; tb_reset_n=1'b0; tb_Ta=1'b1; tb_Tb=1'b0;	
		#5 tb_reset_n=1'b1;
		#10 tb_Tb=1'b1;
		#10 tb_Ta=1'b0;
		#10 tb_Ta=1'b1; tb_Tb=1'b0;
		#10 tb_Ta=1'b0;
		#10 tb_Ta=1'b1;
		#10 tb_Ta=1'b0;
		#10 tb_reset_n=1'b0;
		#10 tb_Tb=1'b1;
		#10 $stop;
	end 
endmodule
`timescale 1ns/100ps
module tb_tl_cntr_w_left;
	reg tb_clk,tb_reset_n,tb_Ta,tb_Tal,tb_Tb,tb_Tbl;
	wire [1:0]tb_La,tb_Lb;
	
	tl_cntr_w_left U0_tl_cntr_w_left(tb_clk,tb_reset_n,tb_Ta,tb_Tal,tb_Tb,tb_Tbl,tb_La,tb_Lb);
	always #5 tb_clk = ~tb_clk; //clock pulse
	
	initial //test cases
		begin
			tb_clk=0;tb_reset_n=0; tb_Ta=0; tb_Tb=0; tb_Tal=0; tb_Tbl=1;
			#5; tb_reset_n=1;
			#10;
			#10; tb_Tb=1;
			#10; tb_Ta=0;
			#10; tb_Ta=1; tb_Tb=0; tb_Tal=1;
			#10; tb_Tal=0;
			#10; tb_Ta=0;
			#10;
			#10; tb_Tbl=0;
			#10; $stop;
		end
endmodule
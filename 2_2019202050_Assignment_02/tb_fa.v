`timescale 1ns/100ps //unit:1ns precision:100ps

module tb_fa;
		reg tb_a,tb_b,tb_ci;//input
		wire tb_s,tb_co;//output
		
		fa U0_fa(tb_a,tb_b,tb_ci,tb_co,tb_s); //calling fa module
		
		initial begin //run once
				tb_a = 0; tb_b = 0; tb_ci = 0;
		#10;	tb_a = 0; tb_b = 0; tb_ci = 1;
		#10;	tb_a = 0; tb_b = 1; tb_ci = 0;
		#10;	tb_a = 0; tb_b = 1; tb_ci = 1;
		#10;	tb_a = 1; tb_b = 0; tb_ci = 0;
		#10;	tb_a = 1; tb_b = 0; tb_ci = 1;
		#10;	tb_a = 1; tb_b = 1; tb_ci = 0;
		#10;	tb_a = 1; tb_b = 1; tb_ci = 1;
		#10;	
		end
		//exhaust verification
endmodule

		
		
		
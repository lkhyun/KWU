`timescale 1ns/100ps //unit:1ns precision:100ps

module tb_mx2;

		reg tb_d0,tb_d1,tb_s; //stored value
		wire tb_y; //Temporarily store values
	
		mx2 tb_mx2(tb_d0,tb_d1,tb_s,tb_y);
		
		initial begin //run once
			  tb_d0 = 0; tb_d1 = 0; tb_s = 0;
		#10; tb_d0 = 0; tb_d1 = 0; tb_s = 1;
		#10; tb_d0 = 0; tb_d1 = 1; tb_s = 0;
		#10; tb_d0 = 0; tb_d1 = 1; tb_s = 1;
		#10; tb_d0 = 1; tb_d1 = 0; tb_s = 0;
		#10; tb_d0 = 1; tb_d1 = 0; tb_s = 1;
		#10; tb_d0 = 1; tb_d1 = 1; tb_s = 0;
		#10; tb_d0 = 1; tb_d1 = 1; tb_s = 1;
		#10;//simulate at 10ns speed
		end
endmodule
	

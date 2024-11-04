`timescale 1ns/100ps //unit:1ns precision:100ps

module tb_ha;
	reg tb_a, tb_b; //input
	wire tb_co, tb_s; //output
	
	ha U0(tb_a,tb_b,tb_co,tb_s);//calling ha module
	
	initial begin //Run once
			tb_a = 0; tb_b = 0;
	#10;	tb_a = 0; tb_b = 1;
	#10;	tb_a = 1; tb_b = 0;
	#10;	tb_a = 1; tb_b = 1;
	#10;
	end
	//exhaust verification
endmodule

`timescale 1ns/100ps //unit:1ns precision:100ps
module mx2(d0,d1,s,y); //2 to 1 mux
	input d0,d1,s;
	output y;
	wire sb,w0,w1; //Temporarily store values
	
_inv iv0(s,sb);
_nand2 nd20(d0,sb,w0);
_nand2 nd21(d1,s,w1);
_nand2 nd22(w0,w1,y);
/* mux logic */

endmodule 
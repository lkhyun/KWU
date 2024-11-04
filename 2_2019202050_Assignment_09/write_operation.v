module write_operation(we,Addr,wEn);
	input we;
	input [2:0]Addr;
	output [7:0] wEn;//select register
	
	wire [7:0] write_w;
	
	_3_to_8_decoder U0_3_to_8_decoder(Addr,write_w);// Which register to write?
	_and2 U1_and2(we,write_w[0],wEn[0]);
	_and2 U2_and2(we,write_w[1],wEn[1]);
	_and2 U3_and2(we,write_w[2],wEn[2]);
	_and2 U4_and2(we,write_w[3],wEn[3]);
	_and2 U5_and2(we,write_w[4],wEn[4]);
	_and2 U6_and2(we,write_w[5],wEn[5]);
	_and2 U7_and2(we,write_w[6],wEn[6]);
	_and2 U8_and2(we,write_w[7],wEn[7]);
	//instance
endmodule

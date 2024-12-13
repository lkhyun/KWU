module ASR32(d_in, shamt, d_out); //module of Arthimetic Shift Right
	input	[31:0]	d_in; //input 
	input	[1:0]	shamt; 
	output [31:0] d_out; //output
	
	//instances 32 4to1 mux
	mx4 U0_mx4(d_in[0],d_in[1],d_in[2], d_in[3],shamt,d_out[0]);
	mx4 U1_mx4(d_in[1],d_in[2],d_in[3], d_in[4],shamt,d_out[1]);
	mx4 U2_mx4(d_in[2],d_in[3],d_in[4], d_in[5],shamt,d_out[2]);
	mx4 U3_mx4(d_in[3],d_in[4],d_in[5], d_in[6],shamt,d_out[3]);
	mx4 U4_mx4(d_in[4],d_in[5],d_in[6], d_in[7],shamt,d_out[4]);
	mx4 U5_mx4(d_in[5],d_in[6],d_in[7], d_in[8],shamt,d_out[5]);	
	mx4 U6_mx4(d_in[6],d_in[7],d_in[8], d_in[9],shamt,d_out[6]);
	mx4 U7_mx4(d_in[7],d_in[8],d_in[9], d_in[10],shamt,d_out[7]);
	mx4 U8_mx4(d_in[8],d_in[9],d_in[10], d_in[11],shamt,d_out[8]);
	mx4 U9_mx4(d_in[9],d_in[10],d_in[11], d_in[12],shamt,d_out[9]);
	mx4 U10_mx4(d_in[10],d_in[11],d_in[12], d_in[13],shamt,d_out[10]);
	mx4 U11_mx4(d_in[11],d_in[12],d_in[13], d_in[14],shamt,d_out[11]);
	mx4 U12_mx4(d_in[12],d_in[13],d_in[14], d_in[15],shamt,d_out[12]);
	mx4 U13_mx4(d_in[13],d_in[14],d_in[15], d_in[16],shamt,d_out[13]);	
	mx4 U14_mx4(d_in[14],d_in[15],d_in[16], d_in[17],shamt,d_out[14]);
	mx4 U15_mx4(d_in[15],d_in[16],d_in[17], d_in[18],shamt,d_out[15]);
	mx4 U16_mx4(d_in[16],d_in[17],d_in[18], d_in[19],shamt,d_out[16]);
	mx4 U17_mx4(d_in[17],d_in[18],d_in[19], d_in[20],shamt,d_out[17]);
	mx4 U18_mx4(d_in[18],d_in[19],d_in[20], d_in[21],shamt,d_out[18]);
	mx4 U19_mx4(d_in[19],d_in[20],d_in[21], d_in[22],shamt,d_out[19]);
	mx4 U20_mx4(d_in[20],d_in[21],d_in[22], d_in[23],shamt,d_out[20]);
	mx4 U21_mx4(d_in[21],d_in[22],d_in[23], d_in[24],shamt,d_out[21]);	
	mx4 U22_mx4(d_in[22],d_in[23],d_in[24], d_in[25],shamt,d_out[22]);
	mx4 U23_mx4(d_in[23],d_in[24],d_in[25], d_in[26],shamt,d_out[23]);
	mx4 U24_mx4(d_in[24],d_in[25],d_in[26], d_in[27],shamt,d_out[24]);
	mx4 U25_mx4(d_in[25],d_in[26],d_in[27], d_in[28],shamt,d_out[25]);
	mx4 U26_mx4(d_in[26],d_in[27],d_in[28], d_in[29],shamt,d_out[26]);
	mx4 U27_mx4(d_in[27],d_in[28],d_in[29], d_in[30],shamt,d_out[27]);
	mx4 U28_mx4(d_in[28],d_in[29],d_in[30], d_in[31],shamt,d_out[28]);
	mx4 U29_mx4(d_in[29],d_in[30],d_in[31], d_in[31],shamt,d_out[29]);	
	mx4 U30_mx4(d_in[30],d_in[31],d_in[31], d_in[31],shamt,d_out[30]);
	mx4 U31_mx4(d_in[31],d_in[31],d_in[31], d_in[31],shamt,d_out[31]);
						
endmodule 
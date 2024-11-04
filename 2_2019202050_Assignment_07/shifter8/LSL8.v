module LSL8(d_in, shamt, d_out); //module of Logic Shift Left
	input	[7:0]	d_in; //input
	input	[1:0]	shamt; //shift amount
	output [7:0] d_out; //output
	
	//instances 8 4to1 mux
	mx4 U0_mx4(d_in[0],1'b0,1'b0,1'b0,shamt,d_out[0]);
	mx4 U1_mx4(d_in[1],d_in[0],1'b0,1'b0,shamt,d_out[1]);
	mx4 U2_mx4(d_in[2],d_in[1],d_in[0],1'b0,shamt,d_out[2]);
	mx4 U3_mx4(d_in[3],d_in[2],d_in[1],d_in[0],shamt,d_out[3]);
	mx4 U4_mx4(d_in[4],d_in[3],d_in[2],d_in[1],shamt,d_out[4]);
	mx4 U5_mx4(d_in[5],d_in[4],d_in[3],d_in[2],shamt,d_out[5]);
	mx4 U6_mx4(d_in[6],d_in[5],d_in[4],d_in[3],shamt,d_out[6]);
	mx4 U7_mx4(d_in[7],d_in[6],d_in[5],d_in[4],shamt,d_out[7]);
	
endmodule
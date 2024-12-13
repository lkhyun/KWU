module cla33(a,b,ci,s);
	input [32:0] a;
	input [31:0] b;
	input ci;
	output [32:0] s;
	wire [8:1] c;
	
cla4 U0_cla4(a[3:0],b[3:0],ci,c[1],s[3:0]);
cla4 U1_cla4(a[7:4],b[7:4],c[1],c[2],s[7:4]);
cla4 U2_cla4(a[11:8],b[11:8],c[2],c[3],s[11:8]);
cla4 U3_cla4(a[15:12],b[15:12],c[3],c[4],s[15:12]);
cla4 U4_cla4(a[19:16],b[19:16],c[4],c[5],s[19:16]);
cla4 U5_cla4(a[23:20],b[23:20],c[5],c[6],s[23:20]);
cla4 U6_cla4(a[27:24],b[27:24],c[6],c[7],s[27:24]);
cla4 U7_cla4(a[31:28],b[31:28],c[7],c[8],s[31:28]);
fa_v2 U8_fa_v2(a[32],1'b0,c[8],s[32]);//1bit operate add

endmodule

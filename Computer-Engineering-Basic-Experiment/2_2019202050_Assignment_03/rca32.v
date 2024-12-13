module rca32(a,b,ci,co,s);
	input [31:0] a,b;
	input ci;
	output [31:0] s;
	output co;
	
	wire [7:1] c; //Handing over the carry
	
rca4 U0_rca4(a[3:0],b[3:0],ci,c[1],s[3:0]);
rca4 U1_rca4(a[7:4],b[7:4],c[1],c[2],s[7:4]);
rca4 U2_rca4(a[11:8],b[11:8],c[2],c[3],s[11:8]);
rca4 U3_rca4(a[15:12],b[15:12],c[3],c[4],s[15:12]);
rca4 U4_rca4(a[19:16],b[19:16],c[4],c[5],s[19:16]);
rca4 U5_rca4(a[23:20],b[23:20],c[5],c[6],s[23:20]);
rca4 U6_rca4(a[27:24],b[27:24],c[6],c[7],s[27:24]);
rca4 U7_rca4(a[31:28],b[31:28],c[7],co,s[31:28]);
//calling rca4 module for serial connection
endmodule

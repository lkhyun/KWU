module read_operation(from_reg0,from_reg1,from_reg2,from_reg3,from_reg4,from_reg5,from_reg6,from_reg7,re,Addr,Data);
	input [31:0] from_reg0,from_reg1,from_reg2,from_reg3,from_reg4,from_reg5,from_reg6,from_reg7;
	input [2:0] Addr;
	input re;
	output [31:0] Data;
	
	_8_to_1_MUX U0_8_to_1_MUX(from_reg0,from_reg1,from_reg2,from_reg3,from_reg4,from_reg5,from_reg6,from_reg7,re,Addr,Data);//which register to read?
	
endmodule

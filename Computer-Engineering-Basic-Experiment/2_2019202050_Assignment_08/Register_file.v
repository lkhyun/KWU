module Register_file(clk, reset_n, we, wAddr, rAddr, wData, rData); //top module design
	input clk,reset_n,we;
	input [2:0] wAddr,rAddr; // write address and read address
	input [31:0] wData; //write data
	output [31:0] rData;//read data
	wire [7:0] wEn; //write enable
	wire [31:0] regout0,regout1,regout2,regout3,regout4,regout5,regout6,regout7; //for moving register to read operation
	
	write_operation U0_write_operation(we,wAddr,wEn);
	register32_8 U1_register32_8(clk,reset_n,wEn,wData,regout0,regout1,regout2,regout3,regout4,regout5,regout6,regout7);
	read_operation U2_read_operation(regout0,regout1,regout2,regout3,regout4,regout5,regout6,regout7,rAddr,rData);
	//instance
	
endmodule
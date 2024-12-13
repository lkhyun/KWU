module ALUwMul(clk, reset_n, S_sel, S_wr, S_addr, S_din, S_dout);
	input clk, reset_n, S_sel, S_wr;
	input [7:0] S_addr;
	input [31:0] S_din;
	output [31:0] S_dout;
	
	reg [31:0] A_in,B_in,code_in,start_in,done_in,clear_in,result1_in,result2_in;
	reg [7:0] en; //write enable
	wire [31:0] operandA, operandB, opcode, opstart, opdone, opclear, result1, result2; //value
	wire [31:0] rdata; //read data
	wire [31:0] alu_result;
	wire [63:0] mul_result;
	wire done,clear;
	
	register32_r_en U0_register_32_r_en(clk, reset_n,en[0],A_in,operandA);
	register32_r_en U1_register_32_r_en(clk, reset_n,en[1],B_in,operandB);
	register32_r_en U2_register_32_r_en(clk, reset_n,en[2],code_in,opcode);
	register32_r_en U3_register_32_r_en(clk, reset_n,en[3],start_in,opstart);
	register32_r_en U4_register_32_r_en(clk, reset_n,en[4],done_in,opdone);
	register32_r_en U5_register_32_r_en(clk, reset_n,en[5],clear_in,opclear);
	register32_r_en U6_register_32_r_en(clk, reset_n,en[6],result1_in,result1);
	register32_r_en U7_register_32_r_en(clk, reset_n,en[7],result2_in,result2);
	
	read_operation U2_read_operation(operandA, operandB, opcode, opstart, opdone, opclear, result1, result2, S_addr[2:0], rdata); //anytime read
	mx2_32bits U3_mx2_32bits(rdata,32'h0,S_wr,S_dout);//read data or 0

	_and2 U0_and2(opdone[1],opdone[0],clear); //when operation finished multiplier clear
	alu32 U1_alu32(operandA, operandB, opcode[3:0], alu_result);
	multiplier U2_multiplier(clk,reset_n,operandA,operandB,opstart[0],clear,done,mul_result);
	
	always@(S_sel,S_wr,S_addr,S_din,operandA,operandB,opcode,opstart,opdone,opclear,result1,result2,mul_result,done,alu_result) begin // write logic
		if(S_sel == 1'b1) begin //slave selection
			
			if(opclear[0] == 1'b1) begin //all register initializing
				A_in <= 32'b0;
				B_in <= 32'b0;
				code_in <= 32'b0;
				start_in <= 32'b0;
				done_in <= 32'b0;
				clear_in <= 32'b0;
				result1_in <= 32'b0;
				result2_in <= 32'b0;
				en[0] <= 1'b1;
				en[1] <= 1'b1;
				en[2] <= 1'b1;
				en[3] <= 1'b1;
				en[4] <= 1'b1;
				en[5] <= 1'b1;
				en[6] <= 1'b1;
				en[7] <= 1'b1;
				end
			else if(opstart[0] == 1'b1) begin //operation start
				A_in <= 32'b0;
				B_in <= 32'b0;
				code_in <= 32'b0;
				start_in <= 32'b0;
				done_in <= 32'h00000002;
				clear_in <= 32'b0;
				result1_in <= 32'b0;
				result2_in <= 32'b0;
				en[0] <= 1'b0;
				en[1] <= 1'b0;
				en[2] <= 1'b0;
				en[3] <= 1'b1;
				en[4] <= 1'b1;
				en[5] <= 1'b0;
				en[6] <= 1'b0;
				en[7] <= 1'b0;
			end
			else if(opcode[3:0] != 4'b1101 && opdone[1:0] == 2'b10) begin //alu
				A_in <= 32'b0;
				B_in <= 32'b0;
				code_in <= 32'b0;
				start_in <= 32'b0;
				done_in <= 32'h00000003;
				clear_in <= 32'b0;
				result1_in <= alu_result;
				result2_in <= 32'b0;
				en[0] <= 1'b0;
				en[1] <= 1'b0;
				en[2] <= 1'b0;
				en[3] <= 1'b0;
				en[4] <= 1'b1;
				en[5] <= 1'b0;
				en[6] <= 1'b1;
				en[7] <= 1'b0;
			end
			else if(opcode[3:0] == 4'b1101 && done == 1'b1 && opdone[1:0] == 2'b10) begin //mul
				A_in <= 32'b0;
				B_in <= 32'b0;
				code_in <= 32'b0;
				start_in <= 32'b0;
				done_in <= 32'h00000003;
				clear_in <= 32'b0;
				result1_in <= mul_result[31:0];
				result2_in <= mul_result[63:32];
				en[0] <= 1'b0;
				en[1] <= 1'b0;
				en[2] <= 1'b0;
				en[3] <= 1'b0;
				en[4] <= 1'b1;
				en[5] <= 1'b0;
				en[6] <= 1'b1;
				en[7] <= 1'b1;
			end
		
			else if(S_addr[2:0] == 3'b000 && opdone[1:0] == 2'b00) begin // operation waiting assign operandA
				A_in <= S_din;
				B_in <= 32'b0;
				code_in <= 32'b0;
				start_in <= 32'b0;
				done_in <= 32'b0;
				clear_in <= 32'b0;
				result1_in <= 32'b0;
				result2_in <= 32'b0;
				en[0] <= S_wr;
				en[1] <= 1'b0;
				en[2] <= 1'b0;
				en[3] <= 1'b0;
				en[4] <= 1'b0;
				en[5] <= 1'b0;
				en[6] <= 1'b0;
				en[7] <= 1'b0;
			end
		
			else if(S_addr[2:0] == 3'b001 && opdone[1:0] == 2'b00) begin // operation waiting assign operandB
				A_in <= 32'b0;
				B_in <= S_din;
				code_in <= 32'b0;
				start_in <= 32'b0;
				done_in <= 32'b0;
				clear_in <= 32'b0;
				result1_in <= 32'b0;
				result2_in <= 32'b0;
				en[0] <= 1'b0;
				en[1] <= S_wr;
				en[2] <= 1'b0;
				en[3] <= 1'b0;
				en[4] <= 1'b0;
				en[5] <= 1'b0;
				en[6] <= 1'b0;
				en[7] <= 1'b0;
			end
		
			else if(S_addr[2:0] == 3'b010 && opdone[1:0] == 2'b00) begin // operation waiting assign opcode
				A_in <= 32'b0;
				B_in <= 32'b0;
				code_in <= S_din;
				start_in <= 32'b0;
				done_in <= 32'b0;
				clear_in <= 32'b0;
				result1_in <= 32'b0;
				result2_in <= 32'b0;
				en[0] <= 1'b0;
				en[1] <= 1'b0;
				en[2] <= S_wr;
				en[3] <= 1'b0;
				en[4] <= 1'b0;
				en[5] <= 1'b0;
				en[6] <= 1'b0;
				en[7] <= 1'b0;
			end
		
			else if(S_addr[2:0] == 3'b011 && opdone[1:0] == 2'b00) begin // operation waiting assign opstart
				A_in <= 32'b0;
				B_in <= 32'b0;
				code_in <= 32'b0;
				start_in <= S_din;
				done_in <= 32'b0;
				clear_in <= 32'b0;
				result1_in <= 32'b0;
				result2_in <= 32'b0;
				en[0] <= 1'b0;
				en[1] <= 1'b0;
				en[2] <= 1'b0;
				en[3] <= S_wr;
				en[4] <= 1'b0;
				en[5] <= 1'b0;
				en[6] <= 1'b0;
				en[7] <= 1'b0;
			end
		
			else if(S_addr[2:0] == 3'b100) begin //assign opdone
				A_in <= 32'b0;
				B_in <= 32'b0;
				code_in <= 32'b0;
				start_in <= 32'b0;
				done_in <= S_din;
				clear_in <= 32'b0;
				result1_in <= 32'b0;
				result2_in <= 32'b0;
				en[0] <= 1'b0;
				en[1] <= 1'b0;
				en[2] <= 1'b0;
				en[3] <= 1'b0;
				en[4] <= S_wr;
				en[5] <= 1'b0;
				en[6] <= 1'b0;
				en[7] <= 1'b0;
			end
		
			else if(S_addr[2:0] == 3'b101) begin //assign opclear
				A_in <= 32'b0;
				B_in <= 32'b0;
				code_in <= 32'b0;
				start_in <= 32'b0;
				done_in <= 32'b0;
				clear_in <= S_din;
				result1_in <= 32'b0;
				result2_in <= 32'b0;
				en[0] <= 1'b0;
				en[1] <= 1'b0;
				en[2] <= 1'b0;
				en[3] <= 1'b0;
				en[4] <= 1'b0;
				en[5] <= S_wr;
				en[6] <= 1'b0;
				en[7] <= 1'b0;
			end
		
			else begin //exception
				A_in <= 32'b0;
				B_in <= 32'b0;
				code_in <= 32'b0;
				start_in <= 32'b0;
				done_in <= 32'b0;
				clear_in <= 32'b0;
				result1_in <= 32'b0;
				result2_in <= 32'b0;
				en <= 8'b00000000;
			end
		end
		else begin //exception
			A_in <= 32'b0;
			B_in <= 32'b0;
			code_in <= 32'b0;
			start_in <= 32'b0;
			done_in <= 32'b0;
			clear_in <= 32'b0;
			result1_in <= 32'b0;
			result2_in <= 32'b0;
			en <= 8'b00000000;
		end
	end
endmodule 
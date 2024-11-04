module fifo(clk, reset_n, rd_en, wr_en,d_in,d_out,full,empty,wr_ack,wr_err,rd_ack,rd_err,data_count);
	input clk,reset_n,rd_en,wr_en;
	input [31:0] d_in;
	output [31:0]d_out;
	output full,empty,wr_ack,wr_err,rd_ack,rd_err; //handshake flag
	output [3:0]data_count;
	
	wire [2:0]cur_state;
	wire [3:0]next_data_count;
	wire [2:0]next_state;
	wire [2:0]cur_head,cur_tail;
	wire we,re;
	wire [2:0] next_head,next_tail;
	wire [31:0] dout;
	
	fifo_ns U0_fifo_ns(wr_en,rd_en,cur_state,data_count,next_state);//next state
	fifo_cal_addr U1_fifo_cal_addr(next_state,cur_head,cur_tail,data_count,we,re,next_head,next_tail,next_data_count); //calculate address
	register3_r U2_register3_r(clk,reset_n,next_state,cur_state); //state register
	register4_r U3_register4_r(clk,reset_n,next_data_count,data_count); //count register
	register3_r U4_register3_r(clk,reset_n,next_head,cur_head); //head register
	register3_r U5_register3_r(clk,reset_n,next_tail,cur_tail); //tail register
	fifo_out U6_fifo_out(cur_state,data_count,full,empty,wr_ack,wr_err,rd_ack,rd_err); //output logic
	Register_file U7_Register_file(clk, reset_n, we,re,cur_tail, cur_head, d_in, dout); //data save
	register32_r_en U8_register32_r_en(clk,reset_n,1,dout,d_out); //data out with clock
	
endmodule
module fifo_ns(wr_en,rd_en,state,data_count,next_state);
	input wr_en,rd_en;
	input [2:0]state;
	input [3:0]data_count;
	output reg [2:0]next_state;
	
	parameter init = 3'b000;
	parameter read = 3'b001;
	parameter write = 3'b010;
	parameter no_op = 3'b011;
	parameter rd_err = 3'b100;
	parameter wr_err = 3'b101;
	//state
	parameter full = 4'b1000;
	parameter empty = 4'b0000;
	//flag
	always@(wr_en,rd_en,state,data_count) begin
		case({wr_en,rd_en,state})
		
			{1'b1,1'b0,init}: next_state <= (data_count == full) ? wr_err : write;
			{1'b1,1'b0,write}: next_state <= (data_count == full) ? wr_err : write;
			{1'b1,1'b0,read}: next_state <= (data_count == full) ? wr_err : write;
			{1'b1,1'b0,wr_err}: next_state <= (data_count == full) ? wr_err : write;
			{1'b1,1'b0,rd_err}: next_state <= (data_count == full) ? wr_err : write;
			{1'b1,1'b0,no_op}: next_state <= (data_count == full) ? wr_err : write;
			//write state
			{1'b0,1'b1,init}: next_state <= (data_count == empty) ? rd_err :read;
			{1'b0,1'b1,write}: next_state <= (data_count == empty) ? rd_err :read;
			{1'b0,1'b1,read}: next_state <= (data_count == empty) ? rd_err :read;
			{1'b0,1'b1,wr_err}: next_state <= (data_count == empty) ? rd_err :read;
			{1'b0,1'b1,rd_err}: next_state <= (data_count == empty) ? rd_err :read;
			{1'b0,1'b1,no_op}: next_state <= (data_count == empty) ? rd_err :read;
			//read state
			{1'b0,1'b0,init}: next_state <= no_op;
			{1'b0,1'b0,write}: next_state <= no_op;
			{1'b0,1'b0,read}: next_state <= no_op;
			{1'b0,1'b0,wr_err}: next_state <= no_op;
			{1'b0,1'b0,rd_err}: next_state <= no_op;
			{1'b0,1'b0,no_op}: next_state <= no_op;
			{1'b1,1'b1,init}: next_state <= no_op;
			{1'b1,1'b1,write}: next_state <= no_op;
			{1'b1,1'b1,read}: next_state <= no_op;
			{1'b1,1'b1,wr_err}: next_state <= no_op;
			{1'b1,1'b1,rd_err}: next_state <= no_op;
			{1'b1,1'b1,no_op}: next_state <= no_op;
			//no operation
			default: next_state <= 3'bx;
		endcase
	end
endmodule
			
			
			
			
			
			
			
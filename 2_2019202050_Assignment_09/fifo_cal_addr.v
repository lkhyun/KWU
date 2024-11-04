module fifo_cal_addr(state,head,tail,data_count,we,re,next_head,next_tail,next_data_count);
	input [2:0] state,head,tail;
	input [3:0] data_count;
	output reg we,re;
	output reg [2:0] next_head,next_tail;
	output reg [3:0] next_data_count;
	
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
	always@(state,head,tail,data_count) begin
		case(state)
			init:	//initializing
				begin
					next_head <= 3'b000;
					next_tail <= 3'b000;
					next_data_count <= empty;
					we <= 1'b0; re <= 1'b0;
				end
				
			read: 
				begin
					next_head <= (head + 3'b001);
					next_tail <= tail;
					next_data_count <= (data_count - 4'b0001);
					we <= 1'b0; re <= 1'b1; //read only
				end
			
			write: 
				begin
					next_head <= head;
					next_tail <= (tail + 3'b001);
					next_data_count <= (data_count + 4'b0001);
					we <= 1'b1; re <= 1'b0; //write only
				end
				
			rd_err: 
				begin
					next_head <= head;
					next_tail <= tail;
					next_data_count <= data_count;
					we <= 1'b0; re <= 1'b0; //no change
				end
			
			wr_err: 
				begin
					next_head <= head;
					next_tail <= tail;
					next_data_count<= data_count;
					we <= 1'b0; re <= 1'b0; //no change
				end
				
			no_op: 
				begin
					next_head <= head;
					next_tail <= tail;
					next_data_count <= data_count;
					we <= 1'b0; re <= 1'b0; //no change
				end
			
			default:
				begin
					next_head <= 3'bx;
					next_tail <= 3'bx;
					next_data_count <= 4'bx;
					we <= 1'bx;
					re <= 1'bx;
				end
			endcase
	end
endmodule
				
module fifo_out(state,data_count,full,empty,wr_acknow,wr_error,rd_acknow,rd_error);
	input [2:0] state;
	input [3:0] data_count;
	output reg full,empty, wr_acknow,wr_error,rd_acknow,rd_error;
	
	parameter init = 3'b000;
	parameter read = 3'b001;
	parameter write = 3'b010;
	parameter no_op = 3'b011;
	parameter rd_err = 3'b100;
	parameter wr_err = 3'b101;
	//state
	always@(state,data_count) begin //flag setting
		case(state)
			init: begin
				full <= 1'b0;
				empty <= 1'b1;
				wr_acknow <= 1'b0;
				wr_error <= 1'b0;
				rd_acknow <= 1'b0;
				rd_error <= 1'b0;
				end
				
			read: begin
				full <= (data_count == 4'b1000) ? 1'b1:1'b0;
				empty <= (data_count == 4'b0000) ? 1'b1:1'b0;
				wr_acknow <= 1'b0;
				wr_error <= 1'b0;
				rd_acknow <= 1'b1;
				rd_error <= 1'b0;
				end
			
			write: begin
				full <= (data_count == 4'b1000) ? 1'b1:1'b0;
				empty <= (data_count == 4'b0000) ? 1'b1:1'b0;
				wr_acknow <= 1'b1;
				wr_error <= 1'b0;
				rd_acknow <= 1'b0;
				rd_error <= 1'b0;
				end
			
			rd_err: begin
				full <= (data_count == 4'b1000) ? 1'b1:1'b0;
				empty <= (data_count == 4'b0000) ? 1'b1:1'b0;
				wr_acknow <= 1'b0;
				wr_error <= 1'b0;
				rd_acknow <= 1'b0;
				rd_error <= 1'b1;
				end
				
			wr_err: begin
				full <= (data_count == 4'b1000) ? 1'b1:1'b0;
				empty <= (data_count == 4'b0000) ? 1'b1:1'b0;
				wr_acknow <= 1'b0;
				wr_error <= 1'b1;
				rd_acknow <= 1'b0;
				rd_error <= 1'b0;
				end
				
			no_op: begin
				full <= (data_count == 4'b1000) ? 1'b1:1'b0;
				empty <= (data_count == 4'b0000) ? 1'b1:1'b0;
				wr_acknow <= 1'b0;
				wr_error <= 1'b0;
				rd_acknow <= 1'b0;
				rd_error <= 1'b0;
				end
			
			default: begin
				full <= 1'bx;
				empty <= 1'bx;
				wr_acknow <= 1'bx;
				wr_error <= 1'bx;
				rd_acknow <= 1'bx;
				rd_error <= 1'bx;
				end
		endcase
	end
endmodule	
			
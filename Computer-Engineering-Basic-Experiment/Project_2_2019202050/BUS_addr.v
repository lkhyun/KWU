module BUS_addr(S_addr,S0_sel,S1_sel);
	input [7:0]S_addr;
	output reg S0_sel,S1_sel;
	
	always@(S_addr) begin
		if((S_addr >= 8'h00) && (S_addr < 8'h20)) begin //slave0 is memory
			S0_sel <= 1'b1;
			S1_sel <= 1'b0;
		end
		else if((S_addr >= 8'h30) && (S_addr < 8'h40)) begin //slave1 is aluwmul
			S0_sel <= 1'b0;
			S1_sel <= 1'b1;
		end
		else begin
			S0_sel <= 1'b0;
			S1_sel <= 1'b0;
		end
	end
endmodule
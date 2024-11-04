module bus_addr(s_address,s0_sel,s1_sel);
	input [7:0]s_address;
	output reg s0_sel,s1_sel;
	
	always@(s_address) begin
		if((s_address >= 8'h00) && (s_address < 8'h20))//00<=address<20 == sel0
			{s0_sel,s1_sel} <= 2'b10;
		else if((s_address >= 8'h20) && (s_address < 8'h40))//20<=address<40 == sel1
			{s0_sel,s1_sel} <= 2'b01;
		else
			{s0_sel,s1_sel} <= 2'b00;
	end
endmodule
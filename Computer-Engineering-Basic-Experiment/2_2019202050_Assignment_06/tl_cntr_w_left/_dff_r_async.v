module _dff_r_async(clk,reset_n,d,q);
	input clk,reset_n,d;
	output q;
	reg q;
	
	always@(posedge clk or negedge reset_n) begin //when clk or reset is changed begin
		if(reset_n == 0) //reset
			q <= 1'b0;
		else
			q <= d; //general
	end
endmodule
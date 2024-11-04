module _dff_rs_async(clk,set,reset,d,q);
	input clk,set,reset,d;
	output q;
	reg q;
	
	always@(posedge clk or negedge set or negedge reset)//set and reset are independent of clk
	begin
		if(reset == 0) q<=1'b0;
		else if(set == 0) q<=1'b1;
		else q<=d;
	end
endmodule
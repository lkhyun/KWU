module _dff_rs_sync(clk,set,reset,d,q);
	input clk,set,reset,d;
	output q;
	reg q;
	
	always@(posedge clk)//set and reset are dependent of clk
	begin
		if(reset == 0) q<=1'b0;
		else if(set == 0) q<=1'b1;
		else q<=d;
		end
endmodule

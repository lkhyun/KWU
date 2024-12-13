module _dff_r(clk,reset,d,q); //resettable dff
	input clk,reset,d;
	output reg q;
	
	always@ (posedge clk or negedge reset) begin //if rising edge or reset  == 0, q = 0
		if(reset==0)
			q <= 1'b0;
		else
			q <=d;
	end
endmodule
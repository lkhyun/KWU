module multiplier(clk,reset_n,multiplier,multiplicand,op_start,op_clear,op_done,result); //multiplier design
	input clk,reset_n,op_start,op_clear;
	input [63:0] multiplier,multiplicand;
	output reg op_done; //operation done?
	output [127:0] result;
	reg [5:0] count;
	reg lastbit;
	reg [63:0] temp1;
	reg [64:0] temp2,temp3;
	reg [64:0] sum,sub;
	reg [64:0] sum2,sub2;
	
	always@(posedge clk or negedge reset_n) begin
		if(reset_n == 0) begin
			count <= 6'b0;
			lastbit <= 1'b0;
			temp1 <= 64'b0;
			temp2 <= 65'b0;
			temp3 <= 65'b0;
			op_done <= 1'b0;
		end
		
		else if(op_clear == 1'b1 && op_start == 1'b0) begin //operation result clear for new multiply
			count <= 6'b0;
			lastbit <= 1'b0;
			temp1 <= 64'b0;
			temp2 <= 65'b0;
			temp3 <= 65'b0;
			op_done <= 1'b0;
		end
		
		else if(op_start == 1'b1 && op_clear == 1'b0) begin //multiply set initializing
			temp1 <= multiplier;
			temp2 <= {multiplicand[63],multiplicand};
			temp3 <= 65'b0;
			lastbit <= 1'b0;
			count <= 6'b100000;
		end
		
		else if(op_clear == 1'b0 && op_start == 1'b0) begin //multiply
			//sum and sub are tools for multiply
			sum = temp3 + temp2;
			sub = temp3 + ((~temp2) + 1'b1);
			sum2 = temp3 + (temp2<<1);
			sub2 = temp3 + ((~temp2+1'b1)<<1);
			case({temp1[1],temp1[0],lastbit})
				{1'b0,1'b0,1'b0}: {temp3,temp1,lastbit} <= {temp3[64],temp3[64],temp3,temp1[63:1]}; //only shift2
				{1'b0,1'b0,1'b1}: {temp3,temp1,lastbit} <= {sum[64],sum[64],sum,temp1[63:1]}; //add once and shift2
				{1'b0,1'b1,1'b0}: {temp3,temp1,lastbit} <= {sum[64],sum[64],sum,temp1[63:1]}; //add once and shift2
				{1'b0,1'b1,1'b1}: {temp3,temp1,lastbit} <= {sum2[64],sum2[64],sum2,temp1[63:1]}; //add twice and shift2
				{1'b1,1'b0,1'b0}: {temp3,temp1,lastbit} <= {sub2[64],sub2[64],sub2,temp1[63:1]}; //substract twice and shift2
				{1'b1,1'b0,1'b1}: {temp3,temp1,lastbit} <= {sub[64],sub[64],sub,temp1[63:1]}; //substract once and shift2
				{1'b1,1'b1,1'b0}: {temp3,temp1,lastbit} <= {sub[64],sub[64],sub,temp1[63:1]}; //substract once and shift2
				{1'b1,1'b1,1'b1}: {temp3,temp1,lastbit} <= {temp3[64],temp3[64],temp3,temp1[63:1]}; //only shift2
				default: {temp3,temp1,lastbit} <= {65'bx,64'bx,1'bx}; //exception
			endcase
			count <= count - 1'b1; //count down
			if(count == 6'b0) begin //when multiply is finished, keep data until op_clear set
				temp1 <= temp1;
				temp2 <= temp2;
				temp3 <= temp3;
				count <= count;
				lastbit <= lastbit;
				op_done <= 1'b1;
			end
		end
		
		else begin //exception
			count <= 6'bx;
			temp1 <= 64'bx;
			temp2 <= 65'bx;
			temp3 <= 65'bx;
			lastbit <= 1'bx;
			op_done <= 1'bx;
		end
	end
	assign result = {temp3[63:0],temp1}; //save data in result
	
endmodule
				
			
			
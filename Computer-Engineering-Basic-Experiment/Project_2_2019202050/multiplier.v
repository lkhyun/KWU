module multiplier(clk,reset_n,multiplier,multiplicand,op_start,op_clear,op_done,result); //multiplier module
	input	clk,reset_n,op_start,op_clear;
	input	[31:0]	multiplicand,multiplier; //A,X
	output reg	op_done;
	output [63:0]	result; //Y = A*X
	reg [64:0] resulttemp; // Y+lastbit
	reg	[31:0]	count;
	reg [64:0] multiplicandtemp1; //{A,32'b0,1'b0}
	reg [64:0] multiplicandtemp2; //{-A,32'b0,1'b0}
	wire [31:0] temp; //-A
	wire 	[31:0] countup;
	wire [64:0] sum,sub;
	wire [64:0] sumandshift,subandshift,onlyshift;
	
	cla32 U0_cla32(32'b0,(~multiplicand),1'b1,temp); //make -A
	cla65 U0_cla65(resulttemp,multiplicandtemp1,1'b0,sum);//make sum
	cla65 U1_cla65(resulttemp,multiplicandtemp2,1'b1,sub);//make sub
	
	cla32 U2_cla32(count,32'b0,1'b1,countup);
	
	ASR65 U3_ASR65(sum,2'b01,sumandshift);
	ASR65 U4_ASR65(sub,2'b01,subandshift);
	ASR65 U5_ASR65(resulttemp,2'b01,onlyshift);
	
	always @ (posedge clk or negedge reset_n) begin
		if (reset_n == 0) begin //reset
			op_done	<= 1'b0;
			count 	<= 32'b0;
			resulttemp <= 65'b0;
			multiplicandtemp1 <= 65'b0;
			multiplicandtemp2 <= 65'b0;
		end
		
		else if (op_start == 1 && op_clear == 0) begin //operate ready
			resulttemp[64:33]	<= 32'b0;
			resulttemp[32:1]	<= multiplier;
			resulttemp[0]	<= 1'b0;
			multiplicandtemp1[64:33] <= multiplicand;
			multiplicandtemp1[32:0] 	<= 33'b0;
			multiplicandtemp2[64:33] <= temp;
			multiplicandtemp2[32:0] 	<= 33'b0;
			count	<= 32'b0;
		end
		
		else if (op_start == 0 && op_clear == 0) begin //operate processing
			if(resulttemp[1] == 1'b0 && resulttemp[0] == 1'b0)
				resulttemp <= onlyshift;
				
			else if(resulttemp[1] == 1'b0 && resulttemp[0] ==1'b1)
				resulttemp <= sumandshift;
			
			else if(resulttemp[1] == 1'b1 && resulttemp[0] ==1'b0)
				resulttemp <= subandshift;
				
			else if(resulttemp[1] == 1'b1 && resulttemp[0] ==1'b1)
				resulttemp <= onlyshift;
			
			else
				resulttemp <= 65'bx;
				
			count <= countup; //count = count + 1
			if (count == 32) begin //keep value
				resulttemp <= resulttemp;
				count		<= count;
				op_done	<= 1'b1;
			end
		end
		
		else if (op_start == 0 && op_clear == 1) begin //clear
			resulttemp <= 65'b0;
			multiplicandtemp1 <= 65'b0;
			multiplicandtemp2 <= 65'b0;
			count		<= 32'b0;
			op_done	<= 1'b0;
		end
		
		else begin
			resulttemp <= 65'bx;
			count	<= 32'bx;
		end
	end
	
	assign result = resulttemp[64:1];
endmodule
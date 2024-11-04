`timescale 1ns/100ps //using self-checking testbench with testvectors of alu32

module tb_alu32;
	
	reg tb_clk, tb_reset; 
	reg [31:0] vectornum, errors; //error and numbers of test
	reg [103:0] testvectors[100:0]; // calling .tv files
	reg [31:0] expected_result; 
	reg expected_c, expected_n, expected_z, expected_v; 
	//expected
	reg [31:0] tb_a, tb_b; 
	reg [2:0] tb_op;  
	reg dummy;
	wire [31:0] tb_result; 
	wire tb_c, tb_n, tb_z, tb_v; 
	//experiment

	alu32 U0_alu32(tb_a, tb_b, tb_op, tb_result, tb_c, tb_n, tb_z, tb_v); 
	always
	begin
		tb_clk = 1; #5; tb_clk = 0; #5; //set clk
	end
	
	initial
		begin
			$readmemh("./../../example.tv",testvectors); // file route
			vectornum=0; errors=0; 
			tb_reset=1; #10; tb_reset=0;
		end
	
	always @ (posedge tb_clk) //acts at posedge
		begin
			#1; {tb_a, tb_b, dummy, tb_op, expected_result, expected_c, expected_n, expected_z, expected_v} = testvectors[vectornum]; //data stored 
		end
	always @ (negedge tb_clk) //acts at negedge
		if(~tb_reset) begin 
				if(tb_result !== expected_result || tb_c !== expected_c || tb_n !== expected_n || tb_z !== expected_z || tb_v !== expected_v) //not matched
			 		begin 
						$display("Error: inputs = a: %h, b: %h, op: %b",tb_a, tb_b, tb_op);
						$display("outputs = result: %h, c: %b, n: %b, z: %b, v: %b (%h %b %b %b %b expected)", tb_result, tb_c, tb_n, tb_z, tb_v, expected_result, expected_c, expected_n, expected_z, expected_v);
						errors = errors + 1; 
					end
				vectornum = vectornum + 1; 
			if(testvectors[vectornum] === 104'hx) // read all?
				begin //display vectornum,errors
					$display("%d tests completed with %d errors", vectornum, errors); 
					$finish;
				end
		end
endmodule

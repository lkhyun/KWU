`timescale 1ns/100ps //using self-checking testbench with testvectors of alu4

module tb_alu4;
	
	reg tb_clk, tb_reset; 
	reg [3:0] vectornum, errors; //error and numbers of test
	reg [19:0] testvectors[100:0]; // calling .tv files
	reg [3:0] expected_result; 
	reg expected_c, expected_n, expected_z, expected_v; 
	//expected
	reg [3:0] tb_a, tb_b; 
	reg [2:0] tb_op;
	wire [3:0] tb_result; 
	wire tb_c, tb_n, tb_z, tb_v; 
	//experiment

	alu4 U0_alu4(tb_a, tb_b, tb_op, tb_result, tb_c, tb_n, tb_z, tb_v); 
	always
	begin
		tb_clk = 1; #5; tb_clk = 0; #5; //set clk
	end
	
	initial
		begin
			$readmemb("./../../example.tv",testvectors); // file route
			vectornum=0; errors=0; 
			tb_reset=1; #10; tb_reset=0;
		end
	
	always @ (posedge tb_clk) //acts at posedge
		begin
			#1; {tb_a, tb_b, tb_op, expected_result, expected_c, expected_n, expected_z, expected_v} = testvectors[vectornum]; //data stored 
		end
	always @ (negedge tb_clk) //acts at negedge
		if(~tb_reset) begin 
				if(tb_result !== expected_result || tb_c !== expected_c || tb_n !== expected_n || tb_z !== expected_z || tb_v !== expected_v) //not matched
			 		begin 
						$display("Error: inputs = a: %b, b: %b, op: %b",tb_a, tb_b, tb_op);
						$display("outputs = result: %b, c: %b, n: %b, z: %b, v: %b (%b %b %b %b %b expected)", tb_result, tb_c, tb_n, tb_z, tb_v, expected_result, expected_c, expected_n, expected_z, expected_v);
						errors = errors + 1; 
					end
				vectornum = vectornum + 1; 
			if(testvectors[vectornum] === 20'bx) // read all?
				begin //display vectornum,errors
					$display("%d tests completed with %d errors", vectornum, errors); 
					$finish;
				end
		end
endmodule
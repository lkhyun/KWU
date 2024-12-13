module cntr8(clk, reset_n, inc, load, d_in, d_out, o_state); //8way counter design
	input	clk,reset_n,inc,load; //input
	input		[7:0]		d_in;
	output	[7:0]		d_out; //output
	output	[2:0]		o_state;
	
	wire		[2:0]		next_state;
	wire		[2:0]		state;
	assign	o_state=state;	
	 //next state instance
	ns_logic 		U0_ns_logic(load, inc, state, next_state);
	//3bit register instance
	_register3_r 	U1_register3_r(clk, reset_n, next_state, state); 
	 //output state logic instance
	os_logic 		U2_os_logic(state, d_in, d_out);
		
endmodule

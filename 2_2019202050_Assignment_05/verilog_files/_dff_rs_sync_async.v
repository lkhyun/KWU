module _dff_rs_sync_async(clk,set,reset,d,q_sync,q_async); //for compare async,sync

	input clk,set,reset,d;
	output q_sync,q_async;
	
	_dff_rs_sync U0_dff_rs_sync(clk,set,reset,d,q_sync);
	_dff_rs_async U0_dff_rs_async(clk,set,reset,d,q_async);
	//calling module
endmodule
	
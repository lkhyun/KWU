module ns_logic(load, inc, state, next_state); //Next state logic design
	
	parameter	IDLE_STATE 	= 3'b000; //count = 0 
	parameter	LOAD_STATE 	= 3'b001; //load input data to count
	parameter	INC_STATE 	= 3'b010; //increment count
	parameter	INC2_STATE 	= 3'b011;
	parameter	DEC_STATE 	= 3'b100; //decrement count
	parameter	DEC2_STATE 	= 3'b101;
	
	input					load, inc; //input
	input		[2:0]		state;
	output	[2:0]		next_state; //output
	
	reg		[2:0]		next_state;
	
	always @ (load, inc, state)
	begin
		case(state)
			IDLE_STATE:
			begin
			if (load == 1'b1) next_state = LOAD_STATE;
			else if(inc == 1'b1) next_state = INC_STATE;
			else next_state = DEC_STATE;
			end	
			
			LOAD_STATE:
			begin
			if (load == 1'b1) next_state = LOAD_STATE;
			else if(inc == 1'b1) next_state = INC_STATE;
			else if(inc == 1'b0) next_state = DEC_STATE;
			else next_state = IDLE_STATE;
			end

			INC_STATE:
			begin
			if(load ==1'b1) next_state=LOAD_STATE;
			else if(inc == 1'b1) next_state = INC2_STATE;
			else if(inc == 1'b0) next_state = DEC_STATE;
			else next_state = IDLE_STATE;
			end
		
			INC2_STATE:
			begin
			if(load ==1'b1) next_state=LOAD_STATE;
			else if(inc == 1'b1) next_state = INC_STATE;
			else if(inc == 1'b0) next_state = DEC_STATE;
			else next_state = IDLE_STATE;
			end
			
			DEC_STATE:
			begin
			if(load ==1'b1) next_state=LOAD_STATE;
			else if(inc == 1'b1) next_state = INC_STATE;
			else if(inc == 1'b0) next_state = DEC2_STATE;
			else next_state = IDLE_STATE;
			end
		
			DEC2_STATE:
			begin
			if(load ==1'b1) next_state=LOAD_STATE;
			else if(inc == 1'b1) next_state = INC_STATE;
			else if(inc == 1'b0) next_state = DEC_STATE;
			else next_state = IDLE_STATE;
			end
			
			default : next_state = 3'bxxx;
		endcase
	end
endmodule

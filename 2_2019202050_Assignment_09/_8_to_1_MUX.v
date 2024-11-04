module _8_to_1_MUX(a,b,c,d,e,f,g,h,re,sel,d_out); //MUX design
	input [31:0]a,b,c,d,e,f,g,h;
	input [2:0] sel; //select
	input re;
	output reg [31:0]d_out;
	
	always@(sel,re,a,b,c,d,e,f,g,h) begin //which one should go out?
		case({sel,re})
			{3'b000,1'b1} :d_out <= a;
			{3'b001,1'b1} :d_out <= b;
			{3'b010,1'b1} :d_out <= c;
			{3'b011,1'b1} :d_out <= d;
			{3'b100,1'b1} :d_out <= e;
			{3'b101,1'b1} :d_out <= f;
			{3'b110,1'b1} :d_out <= g;
			{3'b111,1'b1} :d_out <= h;
			//if re is 1 read enable
			{3'b000,1'b0} :d_out <= 32'h0;
			{3'b001,1'b0} :d_out <= 32'h0;
			{3'b010,1'b0} :d_out <= 32'h0;
			{3'b011,1'b0} :d_out <= 32'h0;
			{3'b100,1'b0} :d_out <= 32'h0;
			{3'b101,1'b0} :d_out <= 32'h0;
			{3'b110,1'b0} :d_out <= 32'h0;
			{3'b111,1'b0} :d_out <= 32'h0;
			//if re is 0 read disable
			default: d_out <= 32'hx;
		endcase
	end
	
endmodule
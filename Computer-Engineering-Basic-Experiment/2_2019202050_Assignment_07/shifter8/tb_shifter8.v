`timescale 1ns/100ps
module tb_shifter8; //8bit shifter testbench

   reg tb_clk, tb_reset;
   reg [2:0]   tb_op;
   reg   [1:0]   tb_shamt;
   reg   [7:0] tb_d_in; //input
   
   wire   [7:0]   tb_d_out; //output

   //8bit shifter instance
   shifter8 U0_shifter8(tb_clk, tb_reset, tb_op, tb_shamt, tb_d_in, tb_d_out);
   
   always #5 tb_clk=~tb_clk; //clock pulse
   
   initial //test
   begin 
      tb_clk=1'b0; tb_reset=1'b0; tb_d_in=8'b1010_1100; tb_shamt=2'b10; tb_op=3'b000; 
		#7 tb_reset=1'b1;
		#5 tb_op=3'b010;
		#10 tb_op=3'b010;
		#10 tb_op=3'b011;
		#10 tb_op=3'b100;
		#10 tb_op=3'b010; tb_shamt = 2'b11;
		#10 tb_op=3'b001;
		#10 tb_op=3'b000;
		#10 tb_reset=1'b0;
		#10 $stop;   
   end
endmodule
   

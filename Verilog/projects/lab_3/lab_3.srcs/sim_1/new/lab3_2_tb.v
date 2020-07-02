`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/14/2020 03:02:31 PM
// Design Name: 
// Module Name: lab3_2_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module lab3_2_tb();
    reg [3:0] D;
    reg clk;
    reg rst;
    reg en;
    wire [3:0] Q;
    
    initial begin
        clk = 1'b0;
        en = 1'b0;
        #200 $stop;
    end
    
    always
        #10 clk = !clk;
    
    always begin
        #40 en=!en;
        #20 en=!en;
    end
    
    initial begin
        rst = 1'b0;
        #80 rst = !rst;
        #50 rst = !rst;
     end
     
     initial begin
         D = 4'b0000;
         #20 D = 4'b0101;
         #40 D = 4'b1001;
     end
     
     Register_synch_reset_load myRegister(D, clk, rst, en, Q);
     
endmodule

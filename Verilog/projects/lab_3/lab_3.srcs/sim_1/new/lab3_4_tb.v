`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/14/2020 04:28:30 PM
// Design Name: 
// Module Name: lab3_4_tb
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


module lab3_4_tb();
    reg clk;
    reg rst;
    reg en;
    wire [3:0] Q;
    
    initial
        clk = 1'b0;
        
    always
        #5 clk = !clk;
        
    initial begin
        rst = 1'b0;
        #40 rst = 1'b1;
        #20 rst = 1'b0;
    end
    
    initial begin
        en = 1'b0;
        #20 en = 1'b1;
        #150 en = 1'b0;
        #40 en = 1'b1;
    end
    
    CNT4_synch_reset_enable myCNT(clk, rst, en, Q);
    
endmodule

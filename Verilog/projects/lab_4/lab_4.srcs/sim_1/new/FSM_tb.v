//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/28/2020 03:03:23 PM
// Design Name: 
// Module Name: FSM_tb
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


`timescale 1ns / 1ps
module FSM_tb();
    reg clk, rst, start, next_zero;

    FSM myFSM(clk,rst,start,next_zero, LD_SUM, LD_NEXT, SUM_SEL, NEXT_SEL, A_SEL, DONE);

    initial begin
        clk = 1'b0;
        #200 $stop;
    end
    
    always
        #10 clk = !clk;
    
    initial begin
        rst = 1'b1;
        #15 rst = 1'b0;
    end

    initial begin
        start = 1'b0;
        #35 start = 1'b1;
        #105 start = 1'b0;
    end
    
    initial begin
        next_zero = 1'b0;
        #110 next_zero = 1'b1;
    end
endmodule


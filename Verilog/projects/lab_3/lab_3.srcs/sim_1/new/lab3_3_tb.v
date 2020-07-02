`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/14/2020 03:45:42 PM
// Design Name: 
// Module Name: lab3_3_tb
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


module lab3_3_tb();
    reg clk;
    reg ShiftEn;
    reg ShiftIn;
    wire [3:0] ParallelOut;
    wire ShiftOut;
    
    initial begin
        clk = 1'b0;
        #300 $stop;
    end
    
    always
        #10 clk = !clk;
    
    initial begin
        ShiftIn = 1'b0;
        #10 ShiftIn = 1'b1;
        #50 ShiftIn = 1'b0;
        #40 ShiftIn = 1'b1;
        #60 ShiftIn = 1'b0;
        #20 ShiftIn = 1'b1;
        #40 ShiftIn = 1'b0;
    end
    
    initial begin
        ShiftEn = 1'b0;
        #40 ShiftEn = 1'b1;
        #60 ShiftEn = 1'b0;
        #40 ShiftEn = 1'b1;
    end
    
    Serial_in_parallel_out_enable mySReg(clk, ShiftEn, ShiftIn, ParallelOut, ShiftOut);
    
endmodule

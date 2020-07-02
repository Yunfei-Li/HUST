//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/28/2020 03:33:11 PM
// Design Name: 
// Module Name: auto_add_tb
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
module auto_add_tb();
    reg clk, rst, start;
    wire [7:0] sum_out;
    wire DONE;

    auto_add #(32, 32, "sum_init.mem")  myAdder(clk,rst,start,DONE,sum_out);

    initial begin
        clk = 1'b0;
        #200 $stop;
    end

    always begin
        #10 clk = !clk;
    end
    
    initial begin
        rst = 1'b1;
        #15 rst = 1'b0;
    end

    initial begin
        start = 1'b0;
        #20 start = 1'b1;
    end
    
endmodule

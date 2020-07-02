`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/07/2020 04:53:32 PM
// Design Name: 
// Module Name: mux_21_b_tb
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


module mux_21_b_tb();
    reg a, b, sel;
    wire out;
    
    mux_21_b be(a,b,sel,out);
    
    initial begin
        a = 1;
        b = 1;
        sel = 1;
        #10 a=0;
        #15 b=0;
        #05 a=1;
        #15 sel=0;
        #10 b=1;
        #05 sel=1;
    end
    
endmodule

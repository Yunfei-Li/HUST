`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/07/2020 04:48:11 PM
// Design Name: 
// Module Name: mux_21_b
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


module mux_21_b(
    input a,
    input b,
    input sel,
    output reg out
    );
    
    always @(a, b, sel)
    begin
        case(sel)
        1'b1: out=b;
        1'b0: out=a;
        endcase
    end
    
endmodule

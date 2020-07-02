`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/21/2020 03:04:16 PM
// Design Name: 
// Module Name: is_equal
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


module is_equal(a, b, c);
    parameter WIDTH = 8;
    
    input [WIDTH-1:0] a;
    input [WIDTH-1:0] b;
    output c;
    
    assign c = (a==b);
    
endmodule

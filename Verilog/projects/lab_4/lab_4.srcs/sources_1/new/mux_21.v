`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/21/2020 03:06:19 PM
// Design Name: 
// Module Name: mux_21
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


module mux_21(a, b, sel, c);
    parameter WIDTH = 8;
    
    input [WIDTH-1:0] a, b;
    input sel;
    output reg [WIDTH-1:0] c;
    
    always @(a, b, sel) begin
        case(sel)
            1'b0: c = a;
            1'b1: c = b;
        endcase
    end
    
endmodule

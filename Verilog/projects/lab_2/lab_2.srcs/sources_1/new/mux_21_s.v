`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/07/2020 04:48:11 PM
// Design Name: 
// Module Name: mux_21_s
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


module mux_21_s(
    input a,
    input b,
    input sel,
    output out
    );
    
    not(sel_, sel);
    and(ao, a, sel_);
    and(bo, b, sel);
    or(out, ao, bo);
    
endmodule
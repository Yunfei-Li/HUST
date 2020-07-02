`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/07/2020 04:48:11 PM
// Design Name: 
// Module Name: mux_21_d
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


module mux_21_d(
    input a,
    input b,
    input sel,
    output out
    );
    
    assign out=(sel&b)|(!sel&a);
    
endmodule

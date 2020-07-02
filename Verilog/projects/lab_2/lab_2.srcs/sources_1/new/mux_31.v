`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/07/2020 06:37:07 PM
// Design Name: 
// Module Name: mux_31
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


module mux_31(
    input u,
    input v,
    input w,
    input [1:0] sel,
    output out
    );
    
    mux_21_b mux_21_1(u,v,sel[0],t);
    mux_21_b mux_21_2(t,w,sel[1],out);
    
endmodule

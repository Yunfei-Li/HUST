`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/14/2020 02:57:10 PM
// Design Name: 
// Module Name: Register_synch_reset_load
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


module Register_synch_reset_load(
    input [3:0] D,
    input clk,
    input rst,
    input en,
    output reg [3:0] Q
    );
    
    always @(posedge clk)
        if (rst) begin
            Q <= 4'b0000;
        end else if (en) begin
            Q <= D;
        end else begin
            Q <= Q;
        end
        
endmodule

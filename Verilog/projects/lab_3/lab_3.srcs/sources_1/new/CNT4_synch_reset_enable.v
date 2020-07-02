`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/14/2020 04:23:43 PM
// Design Name: 
// Module Name: CNT4_synch_reset_enable
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


module CNT4_synch_reset_enable(
    input clk,
    input rst,
    input en,
    output [3:0] Q
    );
    
    reg [3:0] Q1;
    
    always @ (posedge clk)
        if (rst) begin
            Q1 <= 4'b0000;
        end else if (en) begin
            Q1 <= Q1+1;
        end
    
    assign Q = Q1;
        
endmodule

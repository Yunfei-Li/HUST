`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/21/2020 02:55:32 PM
// Design Name: 
// Module Name: register
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


module register(clk, rst_n, en, d, q);
  parameter WIDTH = 8;
  input clk, rst_n, en;
  input [WIDTH-1:0] d;
  output reg [WIDTH-1:0] q;
  always @(posedge clk) begin
    if (rst_n) q <=0;
    else if (en) q <= d;
  end    
endmodule
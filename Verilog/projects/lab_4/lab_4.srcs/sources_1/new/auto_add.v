`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/28/2020 03:27:56 PM
// Design Name: 
// Module Name: auto_add
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


`timescale 1ns / 1ps
module auto_add(clk,rst,start,DONE,sum_out);
    parameter WIDTH = 32;
    parameter ADDR_WIDTH = 32;
    parameter SUM_FILE = "sum_init.mem";
    input clk,rst,start;
    output DONE;
    output [WIDTH-1:0] sum_out;
    
    wire [1:0] State;

    FSM myFSM(clk,rst,start, NEXT_ZERO, LD_SUM, LD_NEXT, SUM_SEL, NEXT_SEL, A_SEL, DONE, State);
    datapath_top #(WIDTH, ADDR_WIDTH, SUM_FILE) myDataPath(clk, rst, SUM_SEL, NEXT_SEL, A_SEL, LD_SUM, LD_NEXT, NEXT_ZERO, sum_out);
    
    assign next_zero = NEXT_ZERO ? 1 : 0 ;
    
endmodule

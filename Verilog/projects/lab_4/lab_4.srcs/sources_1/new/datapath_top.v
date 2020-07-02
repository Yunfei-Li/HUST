`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/21/2020 03:11:42 PM
// Design Name: 
// Module Name: datapath_top
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


module datapath_top(clk, rst, SUM_SEL, NEXT_SEL, A_SEL, LD_SUM, LD_NEXT, NEXT_ZERO, sum_out);
    parameter WIDTH = 8;
    parameter ADDR_WIDTH = 8;
    parameter SUM_FILE = "sum_init.mem";
    
    input clk, rst, SUM_SEL, NEXT_SEL, A_SEL, LD_SUM, LD_NEXT;
    output NEXT_ZERO;
    output [WIDTH-1:0] sum_out;

    wire [WIDTH-1:0] tmp, next_addr, read_addr, sum_tmp, data, next_addr_tmp, data_addr;
    
    
    wire [WIDTH-1:0] low = 'h0;
    wire [WIDTH-1:0] unit = 'h1;
    register #(WIDTH) SUM(clk, rst, LD_SUM, tmp, sum_out);
    register #(WIDTH) NEXT(clk, rst, LD_NEXT, next_addr_tmp, next_addr);
    rom #(WIDTH, ADDR_WIDTH, SUM_FILE) GR(read_addr, data);
    mux_21 #(WIDTH) SUM_MUX(low, sum_tmp, SUM_SEL, tmp);
    mux_21 #(WIDTH) NEXT_MUX(low, data, NEXT_SEL, next_addr_tmp);
    mux_21 #(WIDTH) A_MUX(next_addr, data_addr, A_SEL, read_addr);
    sum #(WIDTH) data_sum(sum_out, data, sum_tmp);
    sum #(WIDTH) inc_addr(unit, next_addr, data_addr);
    is_equal #(WIDTH) endpoint(next_addr_tmp, low, NEXT_ZERO);
endmodule
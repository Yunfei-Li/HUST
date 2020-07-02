`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/14/2020 03:26:52 PM
// Design Name: 
// Module Name: Serial_in_parallel_out_enable
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


module Serial_in_parallel_out_enable(
    input clk,
    input ShiftEn,
    input ShiftIn,
    output [3:0] ParallelOut,
    output ShiftOut
    );
    
    reg [3:0] shift_reg;
    
    always @ (posedge clk)
        if(ShiftEn) begin
            shift_reg <= {ParallelOut[2:0], ShiftIn};
        end
    
    assign ShiftOut = ParallelOut[3];
    assign ParallelOut = shift_reg;
    
endmodule

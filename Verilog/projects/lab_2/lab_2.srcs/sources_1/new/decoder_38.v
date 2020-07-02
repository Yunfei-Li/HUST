`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/07/2020 06:53:57 PM
// Design Name: 
// Module Name: decoder_38
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


module decoder_38(
    input [2:0] CBA,
    output reg [7:0] F
    );
    
    always @(CBA)
    begin
        case(CBA)
        3'b000: F=8'b1111_1110;
        3'b001: F=8'b1111_1101;
        3'b010: F=8'b1111_1011;
        3'b011: F=8'b1111_0111;
        3'b100: F=8'b1110_1111;
        3'b101: F=8'b1101_1111;
        3'b110: F=8'b1011_1111;
        3'b111: F=8'b0111_1111;
        endcase
    end
    
endmodule

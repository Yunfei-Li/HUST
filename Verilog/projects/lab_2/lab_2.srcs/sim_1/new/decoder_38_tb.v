`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/07/2020 06:59:57 PM
// Design Name: 
// Module Name: decoder_38_tb
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


module decoder_38_tb();
    reg [2:0] CBA;
    wire [7:0] F;
    
    decoder_38 dut(CBA, F);
    
    initial begin
        $display ("$time::[CBA] [F] ------");
        $monitor ("%t::", $time, "[%b]\t[%b]", CBA,F);
    end

    initial begin
        CBA=3'b000;
        
        #15 CBA=3'b001;
        #15 CBA=3'b011;
        #15 CBA=3'b010;
        #15 CBA=3'b110;
        #15 CBA=3'b111;
        #15 CBA=3'b101;
        #15 CBA=3'b100;
    end
    
endmodule
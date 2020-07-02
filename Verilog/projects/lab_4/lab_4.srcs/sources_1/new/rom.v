//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/28/2020 04:29:12 PM
// Design Name: 
// Module Name: rom
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
module rom(read_addr, data);
  parameter DATA_WIDTH = 8;
  parameter ADDR_WIDTH = 8;
  parameter INIT_FILE = "sum_init.mem";

  input [ADDR_WIDTH-1:0] read_addr;
  output [DATA_WIDTH-1:0] data;

  reg [DATA_WIDTH-1:0] rom[15:0];

  initial begin
        $readmemh(INIT_FILE, rom);
  end
  
  assign data = rom[read_addr]; 

endmodule

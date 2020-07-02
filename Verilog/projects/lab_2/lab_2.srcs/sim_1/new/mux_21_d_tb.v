`timescale 1ns / 1ps

module mux_21_d_tb();
    reg a, b, sel;
    wire out;
    
    mux_21_d de(a,b,sel,out);
    
    initial begin
        a = 1;
        b = 1;
        sel = 1;
        #10 a=0;
        #15 b=0;
        #05 a=1;
        #15 sel=0;
        #10 b=1;
        #05 sel=1;
    end
    
endmodule
`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/28/2020 02:38:36 PM
// Design Name: 
// Module Name: FSM
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


module FSM(clk,rst,start,next_zero, LD_SUM, LD_NEXT, SUM_SEL, NEXT_SEL, A_SEL, DONE, State);
    input clk,rst,start,next_zero;
    output reg LD_SUM,LD_NEXT,SUM_SEL,NEXT_SEL,A_SEL,DONE;
    output reg [1:0] State;

    parameter START=2'h0, COMPUTE_SUM=2'h1, GET_NEXT=2'h2, FINISHED=2'h3;

    reg [1:0] NextState;

       // CombLogic
    always @(State, start, next_zero) begin
        case (State)

            START: begin                
                LD_SUM <= 1'b0;
                LD_NEXT <= 1'b0;
                SUM_SEL <= 1'b0;
                NEXT_SEL <=  1'b0;
                A_SEL <= 1'b0;
                DONE <= 1'b0;
                if (start == 2'b0) 
                    NextState <= START;
                else 
                    NextState <= COMPUTE_SUM;
            end

            COMPUTE_SUM: begin
                LD_SUM <= 1'b1;
                LD_NEXT <= 1'b0;
                SUM_SEL <= 1'b1;
                NEXT_SEL <=  1'b1;
                A_SEL <= 1'b1;
                DONE <= 1'b0;
                NextState <= GET_NEXT;
            end

            GET_NEXT: begin
                LD_SUM <= 1'b0;
                LD_NEXT <= 1'b1;
                SUM_SEL <= 1'b1;
                NEXT_SEL <=  1'b1;
                A_SEL <= 1'b0;
                DONE <= 1'b0;
                if (next_zero == 1'b0) 
                    NextState <= COMPUTE_SUM;
                else 
                    NextState <= FINISHED;
            end

            FINISHED: begin
                LD_SUM <= 1'b0;
                LD_NEXT <= 1'b0;
                SUM_SEL <= 1'b0;
                NEXT_SEL <=  1'b0;
                A_SEL <= 1'b1;
                DONE <= 1'b1;
                if (start == 1'b0) 
                    NextState <= START;
                else 
                    NextState <= FINISHED;
            end
        endcase 
    end
   
    // StateReg 
    always @(posedge clk) begin
        if (rst == 1'b1 ) 
            State <= START;
        else
            State <= NextState;
    end

endmodule


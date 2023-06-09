//+FHDR----------------------------------------------------------------
// (C) Copyright CASLab.EE.NCKU
// All Right Reserved
//---------------------------------------------------------------------
// FILE NAME: fu_shifter_mask.v
// AUTHOR: Chen-Chien Wang
// CONTACT INFORMATION: ccwang@casmail.ee.ncku.edu.tw
//---------------------------------------------------------------------
// RELEASE VERSION: v2.0
// VERSION DESCRIPTION: First Edition no errata
//---------------------------------------------------------------------
// RELEASE: May 12, 2005  18:34
//---------------------------------------------------------------------
// PURPOSE:
//-FHDR----------------------------------------------------------------

// synopsys translate_off
`include "timescale.v"
// synopsys translate_on

module fu_shifter_mask(din, dout);

        input   [4:0]   din;    // Data input
        output  [31:0]  dout;   // Data Output

        reg     [31:0]  dout;

        always@(din)
        begin

            case(din)
                5'b00000: dout = 32'b00000000000000000000000000000000;
                5'b00001: dout = 32'b10000000000000000000000000000000;
                5'b00010: dout = 32'b11000000000000000000000000000000;
                5'b00011: dout = 32'b11100000000000000000000000000000;
                5'b00100: dout = 32'b11110000000000000000000000000000;
                5'b00101: dout = 32'b11111000000000000000000000000000;
                5'b00110: dout = 32'b11111100000000000000000000000000;
                5'b00111: dout = 32'b11111110000000000000000000000000;
                5'b01000: dout = 32'b11111111000000000000000000000000;
                5'b01001: dout = 32'b11111111100000000000000000000000;
                5'b01010: dout = 32'b11111111110000000000000000000000;
                5'b01011: dout = 32'b11111111111000000000000000000000;
                5'b01100: dout = 32'b11111111111100000000000000000000;
                5'b01101: dout = 32'b11111111111110000000000000000000;
                5'b01110: dout = 32'b11111111111111000000000000000000;
                5'b01111: dout = 32'b11111111111111100000000000000000;
                5'b10000: dout = 32'b11111111111111110000000000000000;
                5'b10001: dout = 32'b11111111111111111000000000000000;
                5'b10010: dout = 32'b11111111111111111100000000000000;
                5'b10011: dout = 32'b11111111111111111110000000000000;
                5'b10100: dout = 32'b11111111111111111111000000000000;
                5'b10101: dout = 32'b11111111111111111111100000000000;
                5'b10110: dout = 32'b11111111111111111111110000000000;
                5'b10111: dout = 32'b11111111111111111111111000000000;
                5'b11000: dout = 32'b11111111111111111111111100000000;
                5'b11001: dout = 32'b11111111111111111111111110000000;
                5'b11010: dout = 32'b11111111111111111111111111000000;
                5'b11011: dout = 32'b11111111111111111111111111100000;
                5'b11100: dout = 32'b11111111111111111111111111110000;
                5'b11101: dout = 32'b11111111111111111111111111111000;
                5'b11110: dout = 32'b11111111111111111111111111111100;
                5'b11111: dout = 32'b11111111111111111111111111111110;

            endcase

        end

endmodule
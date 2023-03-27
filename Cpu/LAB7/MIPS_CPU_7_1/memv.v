// Separate version for the valid bit because of flash clear:

module memv (data_out, addr, data_in, write, clk, rst);
   output data_out;
   input [9:0] addr;
   input       data_in;
   input       write;
   input       clk;
   input       rst;


   reg         mem [0:1023];

   
   integer     i;

   assign      data_out = (write | rst)? 0 : mem[addr];

   always @(negedge clk) begin
      if (rst) begin
         for (i=0; i<1024; i=i+1) begin
            mem[i] = 0; // in hardware this would be a special flash-clear wire!
         end
      end
      if (!rst && write) mem[addr] = data_in;
      
   end
endmodule

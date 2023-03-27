library verilog;
use verilog.vl_types.all;
entity cacheDecide is
    port(
        numout          : out    vl_logic;
        cacheWR         : in     vl_logic;
        rst             : in     vl_logic
    );
end cacheDecide;

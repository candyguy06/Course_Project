library verilog;
use verilog.vl_types.all;
entity memv is
    port(
        data_out        : out    vl_logic;
        addr            : in     vl_logic_vector(10 downto 0);
        data_in         : in     vl_logic;
        write           : in     vl_logic;
        clk             : in     vl_logic;
        rst             : in     vl_logic
    );
end memv;

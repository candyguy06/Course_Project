library verilog;
use verilog.vl_types.all;
entity Cache_Ram is
    generic(
        BitSize         : integer := 1
    );
    port(
        data_out        : out    vl_logic_vector;
        index           : in     vl_logic_vector(9 downto 0);
        data_in         : in     vl_logic_vector;
        write           : in     vl_logic
    );
end Cache_Ram;

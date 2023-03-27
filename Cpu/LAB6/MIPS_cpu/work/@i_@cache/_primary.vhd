library verilog;
use verilog.vl_types.all;
entity I_Cache is
    generic(
        Hit             : integer := 0;
        Miss            : integer := 1;
        Miss_Ready      : integer := 2;
        Reset           : integer := 3
    );
    port(
        clk             : in     vl_logic;
        rst_n           : in     vl_logic;
        CSn             : in     vl_logic;
        ADDR            : in     vl_logic_vector(31 downto 0);
        DO              : out    vl_logic_vector(31 downto 0);
        data_in         : in     vl_logic_vector(127 downto 0);
        IADDR           : out    vl_logic_vector(31 downto 0);
        IREQ            : out    vl_logic;
        cache_stall_n   : out    vl_logic
    );
end I_Cache;

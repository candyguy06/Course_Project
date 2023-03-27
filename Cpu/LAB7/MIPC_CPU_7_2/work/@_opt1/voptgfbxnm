library verilog;
use verilog.vl_types.all;
entity I_Cache is
    generic(
        Hit             : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        Miss            : vl_logic_vector(0 to 1) := (Hi0, Hi1);
        Miss_Ready      : vl_logic_vector(0 to 1) := (Hi1, Hi0);
        Reset           : vl_logic_vector(0 to 1) := (Hi1, Hi1)
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
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of Hit : constant is 1;
    attribute mti_svvh_generic_type of Miss : constant is 1;
    attribute mti_svvh_generic_type of Miss_Ready : constant is 1;
    attribute mti_svvh_generic_type of Reset : constant is 1;
end I_Cache;

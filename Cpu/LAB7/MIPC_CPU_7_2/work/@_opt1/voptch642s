library verilog;
use verilog.vl_types.all;
entity mul_top is
    generic(
        ST_P1           : vl_logic := Hi0;
        ST_P2           : vl_logic := Hi1
    );
    port(
        clk             : in     vl_logic;
        rst_n           : in     vl_logic;
        cs_start        : in     vl_logic;
        cs_sign         : in     vl_logic;
        din_a           : in     vl_logic_vector(31 downto 0);
        din_b           : in     vl_logic_vector(31 downto 0);
        mul_stall       : out    vl_logic;
        product         : out    vl_logic_vector(63 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of ST_P1 : constant is 1;
    attribute mti_svvh_generic_type of ST_P2 : constant is 1;
end mul_top;

library verilog;
use verilog.vl_types.all;
entity mul_fsm is
    generic(
        ST_P1           : vl_logic := Hi0;
        ST_P2           : vl_logic := Hi1
    );
    port(
        clk             : in     vl_logic;
        rst_n           : in     vl_logic;
        cs_start        : in     vl_logic;
        phase           : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of ST_P1 : constant is 1;
    attribute mti_svvh_generic_type of ST_P2 : constant is 1;
end mul_fsm;

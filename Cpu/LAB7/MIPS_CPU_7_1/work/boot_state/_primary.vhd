library verilog;
use verilog.vl_types.all;
entity boot_state is
    generic(
        BS_OFF          : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        BS_FIRST        : vl_logic_vector(0 to 1) := (Hi0, Hi1);
        BS_SECOND       : vl_logic_vector(0 to 1) := (Hi1, Hi0);
        BS_NORMAL       : vl_logic_vector(0 to 1) := (Hi1, Hi1)
    );
    port(
        clk             : in     vl_logic;
        rst_n           : in     vl_logic;
        state           : out    vl_logic_vector(1 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of BS_OFF : constant is 1;
    attribute mti_svvh_generic_type of BS_FIRST : constant is 1;
    attribute mti_svvh_generic_type of BS_SECOND : constant is 1;
    attribute mti_svvh_generic_type of BS_NORMAL : constant is 1;
end boot_state;

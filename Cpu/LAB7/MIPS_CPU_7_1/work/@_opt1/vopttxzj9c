library verilog;
use verilog.vl_types.all;
entity memc is
    generic(
        Size            : integer := 1
    );
    port(
        data_out        : out    vl_logic_vector;
        addr            : in     vl_logic_vector(10 downto 0);
        data_in         : in     vl_logic_vector;
        write           : in     vl_logic;
        clk             : in     vl_logic;
        rst             : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of Size : constant is 1;
end memc;

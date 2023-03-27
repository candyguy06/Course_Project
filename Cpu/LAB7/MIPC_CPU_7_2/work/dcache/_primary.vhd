library verilog;
use verilog.vl_types.all;
entity dcache is
    generic(
        index_size      : integer := 0
    );
    port(
        enable          : in     vl_logic;
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        tag_in          : in     vl_logic_vector(20 downto 0);
        index           : in     vl_logic_vector(10 downto 0);
        data_in         : in     vl_logic_vector(31 downto 0);
        write           : in     vl_logic;
        valid_in        : in     vl_logic;
        datahiz         : in     vl_logic;
        tag_out         : out    vl_logic_vector(20 downto 0);
        data_out        : out    vl_logic_vector(31 downto 0);
        hit             : out    vl_logic;
        valid           : out    vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of index_size : constant is 1;
end dcache;

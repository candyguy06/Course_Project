library verilog;
use verilog.vl_types.all;
entity \_mem_ctrl\ is
    generic(
        IDLE            : vl_logic_vector(0 to 3) := (Hi0, Hi0, Hi0, Hi0);
        READ            : vl_logic_vector(0 to 3) := (Hi0, Hi0, Hi0, Hi1);
        RDMISS          : vl_logic_vector(0 to 3) := (Hi0, Hi0, Hi1, Hi0);
        RDMEM           : vl_logic_vector(0 to 3) := (Hi0, Hi0, Hi1, Hi1);
        RDDATA          : vl_logic_vector(0 to 3) := (Hi0, Hi1, Hi0, Hi0);
        \WRITE\         : vl_logic_vector(0 to 3) := (Hi0, Hi1, Hi0, Hi1);
        WRHIT           : vl_logic_vector(0 to 3) := (Hi0, Hi1, Hi1, Hi0);
        WRMISS          : vl_logic_vector(0 to 3) := (Hi0, Hi1, Hi1, Hi1);
        WRMEM           : vl_logic_vector(0 to 3) := (Hi1, Hi0, Hi0, Hi0);
        RDHIT           : vl_logic_vector(0 to 3) := (Hi1, Hi0, Hi0, Hi1)
    );
    port(
        stall           : out    vl_logic;
        write           : out    vl_logic;
        valid_in        : out    vl_logic;
        wr_mem          : out    vl_logic;
        rd_mem          : out    vl_logic;
        Done            : out    vl_logic;
        CacheHit        : out    vl_logic;
        sel_tag_mem     : out    vl_logic;
        sel_data_cache  : out    vl_logic;
        Rd              : in     vl_logic;
        Wr              : in     vl_logic;
        hit             : in     vl_logic;
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        valid           : in     vl_logic;
        mem_change      : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of IDLE : constant is 1;
    attribute mti_svvh_generic_type of READ : constant is 1;
    attribute mti_svvh_generic_type of RDMISS : constant is 1;
    attribute mti_svvh_generic_type of RDMEM : constant is 1;
    attribute mti_svvh_generic_type of RDDATA : constant is 1;
    attribute mti_svvh_generic_type of \WRITE\ : constant is 1;
    attribute mti_svvh_generic_type of WRHIT : constant is 1;
    attribute mti_svvh_generic_type of WRMISS : constant is 1;
    attribute mti_svvh_generic_type of WRMEM : constant is 1;
    attribute mti_svvh_generic_type of RDHIT : constant is 1;
end \_mem_ctrl\;

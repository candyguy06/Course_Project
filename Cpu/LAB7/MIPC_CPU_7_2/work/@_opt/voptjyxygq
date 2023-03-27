library verilog;
use verilog.vl_types.all;
entity cpu_if is
    generic(
        BS_OFF          : vl_logic_vector(0 to 1) := (Hi0, Hi0);
        BS_FIRST        : vl_logic_vector(0 to 1) := (Hi0, Hi1);
        BS_SECOND       : vl_logic_vector(0 to 1) := (Hi1, Hi0);
        BS_NORMAL       : vl_logic_vector(0 to 1) := (Hi1, Hi1)
    );
    port(
        clk             : in     vl_logic;
        rst_n           : in     vl_logic;
        imem_databus    : in     vl_logic_vector(31 downto 0);
        irq             : in     vl_logic_vector(7 downto 0);
        stall_n         : in     vl_logic;
        id_pc_src       : in     vl_logic_vector(1 downto 0);
        if_intctl_epc   : in     vl_logic_vector(31 downto 0);
        id_add_out      : in     vl_logic_vector(31 downto 0);
        id_jump_pc      : in     vl_logic_vector(31 downto 0);
        id_rs_data      : in     vl_logic_vector(31 downto 0);
        imem_addr       : out    vl_logic_vector(31 downto 0);
        imem_read       : out    vl_logic;
        iack            : in     vl_logic;
        id_pca4         : out    vl_logic_vector(31 downto 0);
        id_ins          : out    vl_logic_vector(31 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of BS_OFF : constant is 1;
    attribute mti_svvh_generic_type of BS_FIRST : constant is 1;
    attribute mti_svvh_generic_type of BS_SECOND : constant is 1;
    attribute mti_svvh_generic_type of BS_NORMAL : constant is 1;
end cpu_if;

library verilog;
use verilog.vl_types.all;
entity cpu_top is
    port(
        CLK             : in     vl_logic;
        RESETn          : in     vl_logic;
        IRQ             : in     vl_logic_vector(5 downto 0);
        IREQn           : out    vl_logic;
        IADDR           : out    vl_logic_vector(31 downto 0);
        IDBUS           : in     vl_logic_vector(127 downto 0);
        DREQn           : out    vl_logic;
        DWRITE          : out    vl_logic;
        DBE             : out    vl_logic_vector(3 downto 0);
        DADDR           : out    vl_logic_vector(31 downto 0);
        DWDBUS          : out    vl_logic_vector(31 downto 0);
        DRDBUS          : in     vl_logic_vector(31 downto 0);
        BIGENDIAN       : in     vl_logic;
        IACK            : out    vl_logic;
        hitc            : out    vl_logic_vector(9 downto 0);
        totalc          : out    vl_logic_vector(9 downto 0);
        DataOut_test    : out    vl_logic_vector(31 downto 0);
        d_cache_stall_n : out    vl_logic;
        dc_wren         : out    vl_logic;
        dc_rden         : out    vl_logic
    );
end cpu_top;

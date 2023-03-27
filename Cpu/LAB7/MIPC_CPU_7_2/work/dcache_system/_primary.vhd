library verilog;
use verilog.vl_types.all;
entity dcache_system is
    port(
        DataOut         : out    vl_logic_vector(31 downto 0);
        Done            : out    vl_logic;
        Stall_n         : out    vl_logic;
        CacheHit        : out    vl_logic;
        addr_mem        : out    vl_logic_vector(31 downto 0);
        wr_mem          : out    vl_logic;
        rd_mem          : out    vl_logic;
        hitc            : out    vl_logic_vector(9 downto 0);
        totalc          : out    vl_logic_vector(9 downto 0);
        DataOut_test    : out    vl_logic_vector(31 downto 0);
        req             : in     vl_logic;
        Addr            : in     vl_logic_vector(31 downto 0);
        DataIn          : in     vl_logic_vector(31 downto 0);
        Rd              : in     vl_logic;
        Wr              : in     vl_logic;
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        data_out_mem    : in     vl_logic_vector(31 downto 0)
    );
end dcache_system;

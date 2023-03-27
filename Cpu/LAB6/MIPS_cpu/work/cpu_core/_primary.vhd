library verilog;
use verilog.vl_types.all;
entity cpu_core is
    port(
        CLK             : in     vl_logic;
        RESETn          : in     vl_logic;
        IRQ             : in     vl_logic_vector(7 downto 0);
        I_Cache_REQ     : out    vl_logic;
        I_Cache_ADDR    : out    vl_logic_vector(31 downto 0);
        I_Cache_DBUS    : in     vl_logic_vector(31 downto 0);
        cache_stall_n   : in     vl_logic;
        DREQ            : out    vl_logic;
        DWRITE          : out    vl_logic;
        DBE             : out    vl_logic_vector(3 downto 0);
        DADDR           : out    vl_logic_vector(31 downto 0);
        DWDBUS          : out    vl_logic_vector(31 downto 0);
        DRDBUS          : in     vl_logic_vector(31 downto 0);
        BIGENDIAN       : in     vl_logic;
        IACK            : out    vl_logic;
        CPWDBUS         : out    vl_logic_vector(31 downto 0);
        CPWREN          : out    vl_logic;
        CPWRNUM         : out    vl_logic_vector(4 downto 0);
        CPRRNUM         : out    vl_logic_vector(4 downto 0);
        CPRRSEL         : out    vl_logic;
        CPRDBUS         : in     vl_logic_vector(31 downto 0)
    );
end cpu_core;

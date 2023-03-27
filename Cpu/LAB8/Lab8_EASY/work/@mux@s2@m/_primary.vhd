library verilog;
use verilog.vl_types.all;
entity MuxS2M is
    port(
        HCLK            : in     vl_logic;
        HRESETn         : in     vl_logic;
        HSELDefault     : in     vl_logic;
        HSEL_Slave1     : in     vl_logic;
        HSEL_Slave2     : in     vl_logic;
        HSEL_Slave3     : in     vl_logic;
        HSEL_Slave4     : in     vl_logic;
        HSEL_Slave5     : in     vl_logic;
        HSEL_Slave6     : in     vl_logic;
        HRDATA_S1       : in     vl_logic_vector(31 downto 0);
        HREADY_S1       : in     vl_logic;
        HRESP_S1        : in     vl_logic_vector(1 downto 0);
        HRDATA_S2       : in     vl_logic_vector(31 downto 0);
        HREADY_S2       : in     vl_logic;
        HRESP_S2        : in     vl_logic_vector(1 downto 0);
        HRDATA_S3       : in     vl_logic_vector(31 downto 0);
        HREADY_S3       : in     vl_logic;
        HRESP_S3        : in     vl_logic_vector(1 downto 0);
        HRDATA_S4       : in     vl_logic_vector(31 downto 0);
        HREADY_S4       : in     vl_logic;
        HRESP_S4        : in     vl_logic_vector(1 downto 0);
        HRDATA_S5       : in     vl_logic_vector(31 downto 0);
        HREADY_S5       : in     vl_logic;
        HRESP_S5        : in     vl_logic_vector(1 downto 0);
        HRDATA_S6       : in     vl_logic_vector(31 downto 0);
        HREADY_S6       : in     vl_logic;
        HRESP_S6        : in     vl_logic_vector(1 downto 0);
        HREADYDefault   : in     vl_logic;
        HRESPDefault    : in     vl_logic_vector(1 downto 0);
        HRDATA          : out    vl_logic_vector(31 downto 0);
        HREADY          : out    vl_logic;
        HRESP           : out    vl_logic_vector(1 downto 0)
    );
end MuxS2M;

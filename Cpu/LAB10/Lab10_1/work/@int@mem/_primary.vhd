library verilog;
use verilog.vl_types.all;
entity IntMem is
    generic(
        MemSize         : integer := 1;
        FileName        : string  := "";
        BaseAddr        : integer := 0
    );
    port(
        HCLK            : in     vl_logic;
        HRESETn         : in     vl_logic;
        HADDR           : in     vl_logic_vector(31 downto 0);
        HTRANS          : in     vl_logic_vector(1 downto 0);
        HWRITE          : in     vl_logic;
        HSIZE           : in     vl_logic_vector(2 downto 0);
        HWDATA          : in     vl_logic_vector(31 downto 0);
        HSEL            : in     vl_logic;
        HREADYin        : in     vl_logic;
        HRDATA          : out    vl_logic_vector(31 downto 0);
        HREADYout       : out    vl_logic;
        HRESP           : out    vl_logic_vector(1 downto 0)
    );
end IntMem;

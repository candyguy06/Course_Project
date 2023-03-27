library verilog;
use verilog.vl_types.all;
entity I_Cache_Controller is
    port(
        clk             : in     vl_logic;
        RA              : in     vl_logic_vector(29 downto 0);
        Cache_En        : in     vl_logic;
        Cache_Hit       : in     vl_logic;
        fill_finish     : out    vl_logic;
        WEn             : out    vl_logic;
        REn             : out    vl_logic;
        OEn             : out    vl_logic
    );
end I_Cache_Controller;

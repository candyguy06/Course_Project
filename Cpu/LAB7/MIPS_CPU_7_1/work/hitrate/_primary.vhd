library verilog;
use verilog.vl_types.all;
entity hitrate is
    port(
        hitc            : out    vl_logic_vector(9 downto 0);
        totalc          : out    vl_logic_vector(9 downto 0);
        cs              : in     vl_logic_vector(3 downto 0);
        rst             : in     vl_logic;
        clk             : in     vl_logic
    );
end hitrate;

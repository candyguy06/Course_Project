library verilog;
use verilog.vl_types.all;
entity change_signal is
    port(
        change          : out    vl_logic;
        data            : in     vl_logic_vector(31 downto 0);
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        en              : in     vl_logic
    );
end change_signal;

library verilog;
use verilog.vl_types.all;
entity interrupt_controller is
    port(
        irq             : in     vl_logic_vector(7 downto 0);
        rst_n           : in     vl_logic;
        clk             : in     vl_logic;
        if_pc           : in     vl_logic_vector(31 downto 0);
        epc             : out    vl_logic_vector(31 downto 0);
        status          : out    vl_logic_vector(31 downto 0);
        cause           : out    vl_logic_vector(31 downto 0);
        iack            : out    vl_logic;
        in_isr          : in     vl_logic
    );
end interrupt_controller;

library verilog;
use verilog.vl_types.all;
entity MMU is
    port(
        clk             : in     vl_logic;
        rst_n           : in     vl_logic;
        nWAIT           : in     vl_logic;
        Cache_Enable    : in     vl_logic;
        Round_Robin     : in     vl_logic;
        Entry_MVA       : in     vl_logic_vector(26 downto 0);
        TLB_Check       : in     vl_logic;
        ROM_Protection  : in     vl_logic;
        System_Protection: in     vl_logic;
        Alignment_Fault_Enable: in     vl_logic;
        MMU_Enable      : in     vl_logic;
        TTB             : in     vl_logic_vector(17 downto 0);
        DACR            : in     vl_logic_vector(31 downto 0);
        Invalidat_TLB   : in     vl_logic;
        Invalidat_TLB_MVA: in     vl_logic;
        TLB_Entry_MVA   : in     vl_logic_vector(21 downto 0);
        FSR             : out    vl_logic_vector(7 downto 0);
        FSR_we          : out    vl_logic;
        FAR             : out    vl_logic_vector(31 downto 0);
        FAR_we          : out    vl_logic;
        nMREQ           : in     vl_logic;
        MVA             : in     vl_logic_vector(31 downto 0);
        Data_phase_nTRANS: in     vl_logic;
        Data_phase_MAS  : in     vl_logic_vector(1 downto 0);
        Data_phase_nRW  : in     vl_logic;
        EXT_ABORT       : in     vl_logic;
        Data_phase_EXT_Enable: out    vl_logic;
        TLB_Miss        : out    vl_logic;
        Data_phase_Cacheable: out    vl_logic;
        Data_phase_Bufferable: out    vl_logic;
        Data_phase_PA   : out    vl_logic_vector(31 downto 0);
        Write_Buffer_Enable: out    vl_logic;
        ABORT           : out    vl_logic;
        MMU_nWAIT       : out    vl_logic;
        HRDATAM         : in     vl_logic_vector(31 downto 0);
        HREADYM         : in     vl_logic;
        HADDRM          : out    vl_logic_vector(31 downto 0);
        HTRANSM         : out    vl_logic_vector(1 downto 0);
        HWRITEM         : out    vl_logic;
        HSIZEM          : out    vl_logic_vector(2 downto 0);
        HBURSTM         : out    vl_logic_vector(2 downto 0);
        HPROTM          : out    vl_logic_vector(3 downto 0);
        HWDATAM         : out    vl_logic_vector(31 downto 0);
        HBUSREQM        : out    vl_logic;
        HLOCKM          : out    vl_logic
    );
end MMU;

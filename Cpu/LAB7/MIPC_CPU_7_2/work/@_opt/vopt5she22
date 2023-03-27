library verilog;
use verilog.vl_types.all;
entity testbench is
    generic(
        CCT             : integer := 10;
        PERIOD          : vl_notype;
        PHASETIME       : vl_notype;
        ABC             : vl_notype
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of CCT : constant is 1;
    attribute mti_svvh_generic_type of PERIOD : constant is 3;
    attribute mti_svvh_generic_type of PHASETIME : constant is 3;
    attribute mti_svvh_generic_type of ABC : constant is 3;
end testbench;

sde-as code.s -mcpu=4km -o code.o
sde-as mips_load.s -mcpu=4km -o mips_load.o
sde-as mips_shift.s -mcpu=4km -o mips_shift.o
sde-as mips_arithm.s -mcpu=4km -o mips_arithm.o 
sde-as mips_move.s -mcpu=4km -o mips_move.o
sde-as mips_mul.s -mcpu=4km -o mips_mul.o
sde-ld code.o mips_load.o mips_shift.o mips_arithm.o mips_move.o mips_mul.o -EB -Ttext 0x40000000 -o code.image
sde-objdump code.image -D > code.txt
sde-conv code.image -o code.conv
rm *.o
rm *.image
rm *.bak
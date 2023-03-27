sde-gcc fib.c -EB -S -O -mcpu=4km -mips32 -mbranch-likely=no -mno-float fib.s
sde-as fib.s -mcpu=4km -o fib.o
sde-ld fib.o  -Ttext 0x40000000 -o fib.image
sde-objdump fib.image -D > fib.txt
sde-conv fib.image -o fib.conv
rm *.o
rm *.image
rm *.bak
sde-gcc heapsort.c -EB -S -O -mcpu=4km -mips32 -mbranch-likely=no -mno-float heapsort.s
sde-as heapsort.s -mcpu=4km -o heapsort.o
sde-ld heapsort.o  -Ttext 0x40000000 -o heapsort.image
sde-objdump heapsort.image -D > heapsort.txt
sde-conv heapsort.image -o heapsort.conv
rm *.o
rm *.image
rm *.bak

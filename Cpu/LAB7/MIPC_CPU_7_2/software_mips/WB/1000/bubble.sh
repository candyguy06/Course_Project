sde-gcc bubble.c -EB -S -O -mips32 -mbranch-likely=no -mno-float -o bubble.s
sde-as bubble.s -g -march=4km -o bubble.o
sde-ld bubble.o -Ttext 0x00008000 -o bubble.image
sde-objdump bubble.image -D > bubble.txt
sde-conv bubble.image -o bubble.conv
rm *.o
rm *.image
rm *.bak

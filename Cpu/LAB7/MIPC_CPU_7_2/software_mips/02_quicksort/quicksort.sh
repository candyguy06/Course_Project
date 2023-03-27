sde-gcc quicksort.c -EB -S -O -mips32 -mbranch-likely=no -mno-float quicksort.s
sde-as quicksort.s -march=4km -o quicksort.o
sde-ld quicksort.o  -Ttext 0x00008000 -o quicksort.image
sde-objdump quicksort.image -D > quicksort.txt
sde-conv quicksort.image -o quicksort.conv
rm *.o
rm *.image
rm *.bak

armasm init.s --cpu=4 -o init.o --unsafe
armcc main_function.c -O2 --cpu=4 -c -o main_function.o
armcc isr.c -O2 --cpu=4 -c -o isr.o
armlink init.o main_function.o isr.o -o code.axf --scatter scatter.sc
fromelf -c -text -o code.txt code.axf
fromELF code.axf -o testcode.txt -vhx -32x1 
del *.o
pause

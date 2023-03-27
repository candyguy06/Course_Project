sde-as system.s -o system.o
sde-ld system.o -EB -Ttext 0x00000000 -o system.image
sde-objdump system.image -D > system.txt
sde-conv system.image -o system.conv
rm *.o
rm *.image
rm *.bak
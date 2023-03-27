CC	= armcc
CCFLAG	= -O2 --cpu=4
AS	= armasm
ASFLAG	= -O2 --cpu=4 --unsafe --nowarn
OBJFILES = init.o main_function.o isr.o


all: test

.PHONY: test clean all

testcode.axf: $(OBJFILES)
	armlink $(OBJFILES) --scatter scatter.sc -o testcode.axf
	fromelf -c --text -o testcode.txt testcode.axf
	fromelf testcode.axf -o ../testcode.txt --vhx --32x1

test: testcode.axf

%.o: %.c
	$(CC) $< $(CPPFLAG) -c -o $@

%.o: %.s
	$(AS) $< $(ASFLAG) -o $@
	
clean:
	rm -rf *~ *.o *.axf *.mif *.bak *.txt movecode
	rm -rf ../*.txt


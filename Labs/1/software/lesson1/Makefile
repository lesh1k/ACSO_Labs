#Note: this makefile doesn't suck and shouldn't require gmake like old versions did

CC = gcc
LD = ld

CFLAGS = -c -O -I. -m32

OBJS = main.o
 
KERNELFN = kernel.elf
FLOPPY_IMG = helloworld.img

$(FLOPPY_IMG): $(KERNELFN)
	./bootmaker helloworld.ini $@ -floppy
	echo "\n"
	wc $(FLOPPY_IMG)

$(KERNELFN): $(OBJS)
	$(LD) -o $@ $(OBJS) -dn -Ttext=0x101080 -melf_i386

clean:
	rm -f $(OBJS) $(KERNELFN) $(FLOPPY_IMG)
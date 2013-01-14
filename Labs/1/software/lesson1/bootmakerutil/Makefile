CC=gcc
CFLAGS=-O2 
#-DxBIG_ENDIAN	#add this line to the CFLAGS if your machine is Big Endian
#NETSTUFF=-lsocket -lnsl  #Add this if netboot won't compile, needed for Suns

all: netboot bootmaker dumphex

netboot: netboot.o
	$(CC) -o netboot netboot.o $(NETSTUFF)

bootmaker: bootmaker.o
	$(CC) -o bootmaker bootmaker.o

dumphex: dumphex.o
	$(CC) -o dumphex dumphex.o

dumph: dumph.o
	$(CC) -o dumph dumph.o

bootblock.h: dumph bootsect.bin
	./dumph bootsect.bin > bootblock.h

clean:
	rm -f netboot bootmaker dumphex *.o *~

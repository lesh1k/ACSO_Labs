#include "bloader.h"

void kern_main();

void _start(int memSize, char *parms, struct boot_dir *loadedfiles)
{
	kern_main();

	asm("cli");
	asm("hlt");
}

void kern_main()
{
	char *vidmem = (char *) 0xb8000;
	
	/* "Hello " */
	vidmem[0] = 'H';
	vidmem[1] = 0x4f;
	vidmem[2] = 'e';
	vidmem[3] = 0x4f;
	vidmem[4] = 'l';
	vidmem[5] = 0x4f;
	vidmem[6] = 'l';
	vidmem[7] = 0x4f;
	vidmem[8] = 'o';
	vidmem[9] = 0x4f;
	vidmem[10] = ' ';
	vidmem[11] = 0xf;

	/* "World " */
	vidmem[12] = 'W';
	vidmem[13] = 0x1f;
	vidmem[14] = 'o';
	vidmem[15] = 0x3f;
	vidmem[16] = 'r';
	vidmem[17] = 0x2f;
	vidmem[18] = 'l';
	vidmem[19] = 0x5f;
	vidmem[20] = 'd';
	vidmem[21] = 0x6f;
	vidmem[22] = ' ';
	vidmem[23] = 0xf;

	/* "OS" */
	vidmem[24] = 'O';
	vidmem[25] = 0xdf;
	vidmem[26] = 'S';
	vidmem[27] = 0xef;

	/* "Balls " */
	vidmem[28] = ' ';
	vidmem[29] = 0xf;
	vidmem[30] = 'B';
	vidmem[31] = 0xf;
	vidmem[32] = 'D';
	vidmem[33] = 0xf;
	vidmem[34] = 'Y';
	vidmem[35] = 0xf;
	vidmem[36] = '7';
	vidmem[37] = 0xf;
	vidmem[38] = '7';
	vidmem[39] = 0xf;
}

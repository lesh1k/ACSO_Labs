#include <stdio.h>

static void dump(unsigned char *x, int sections)
{
    int i;
    
    for(i=0;i<sections;i++){
        printf("%08x: %02x %02x %02x %02x  %02x %02x %02x %02x  %02x %02x %02x %02x  %02x %02x %02x %02x\n",
                16*i,x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7],
                x[8],x[9],x[10],x[11],x[12],x[13],x[14],x[15]);
	x += 16;
    }
}

int main(int argc, char *argv[])
{
	FILE *fp;
	unsigned char buf[4096*3];
	if(fp = fopen(argv[1],"r")){
		fread(buf,1,4096*3,fp);
		dump(buf,4096*3/16);
		fclose(fp);
	}
}

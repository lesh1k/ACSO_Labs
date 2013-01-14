#pragma pack(2)

typedef struct 
{
    unsigned short cmd;  
    unsigned short blk;  
    unsigned char data[1024];
} net_boot;

#define NETBOOT_CMD_LOAD 1
#define NETBOOT_CMD_EXEC 2
#define NETBOOT_CMD_ACK  3

#define NETBOOT_PORT 4242

#define NETBOOT_BASE 0x00100000

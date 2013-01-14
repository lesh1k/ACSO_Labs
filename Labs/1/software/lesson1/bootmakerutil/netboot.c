#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>

#include "netboot.h"

int main(int argc, char *argv[])
{
    struct sockaddr_in dst,src;
    char buf[128];
    net_boot nb;
    int fd;
    
    int s,l,i;

    if(argc != 3) {
        fprintf(stderr,"usage: test <filename> <addr>\n");
        exit(1);
        
    }        
    dst.sin_family = AF_INET;
    dst.sin_addr.s_addr = inet_addr(argv[2]);
    dst.sin_port = htons(NETBOOT_PORT);

    src.sin_family = AF_INET;
    src.sin_addr.s_addr = htonl(INADDR_ANY);
    src.sin_port = htons(NETBOOT_PORT);
    
    if((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        perror("socket");

    if(bind(s, (struct sockaddr *) &src, sizeof(src)) == -1)
        perror("bind");

    fprintf(stderr,"loading [");
    
    fd = open(argv[1],O_RDONLY);

    i = 0;
    
    while(read(fd,&(nb.data),1024) > 0){
        nb.cmd = htons(NETBOOT_CMD_LOAD);
        nb.blk = htons(i);
        
        if(sendto(s, &nb, sizeof(nb), 0, (struct sockaddr *) &dst, sizeof(dst))
           == -1){
            perror("sendto");
        }

        if(recvfrom(s,&nb,sizeof(nb),0,NULL,NULL) < 0) perror("recvfrom");
        if(nb.cmd == htons(NETBOOT_CMD_ACK)) fprintf(stderr,".");

        i++;
    }

    nb.cmd = htons(NETBOOT_CMD_EXEC);
    nb.blk = htons(0);
    
    if(sendto(s, &nb, 4, 0, (struct sockaddr *) &dst, sizeof(dst))
       == -1){
        perror("sendto");
    }
    
/*    if(recvfrom(s,&nb,sizeof(nb),0,NULL,NULL) < 0) perror("recvfrom");
    if(nb.cmd == htons(NETBOOT_CMD_ACK)) fprintf(stderr,"!");*/
    
    fprintf(stderr,"] done\n");
    
    close(s);
    
    return 0;
    
}

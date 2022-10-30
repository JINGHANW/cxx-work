#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
int main() {
    int socketfd;
    socklen_t addr_len;
    char buf[64];
    memset(buf,0,64*sizeof(char));
    struct sockaddr_in server_addr;

    if((socketfd = socket(PF_INET,SOCK_DGRAM,0)) < 0)
    {
        perror("socket");
        exit(-1);
    }
    printf("socketfd = %d\n",socketfd);

    int i=1;
    socklen_t len = sizeof(i);

    setsockopt(socketfd,SOL_SOCKET,SO_BROADCAST,&i,len);


    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("192.168.21.61");
    server_addr.sin_port = htons(8000);
    addr_len=sizeof(server_addr);

    while(1)
    {

        fgets(buf,64,stdin);
        int length = sendto(socketfd,buf,64,0,(struct sockaddr*)&server_addr,addr_len);
        printf("length =%d\n",length);
        if(length < 0)
        {

            perror("sendrto");
            exit(-1);
        }
        if(strncmp(buf,"quit",4) == 0)
            break;
    }

    close(socketfd);
    return 0;
}

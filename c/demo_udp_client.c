#include "demo.pb-c.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int args, char *argv[]){
    
    int sock = -1;
    int ret = -1;
    struct sockaddr_in mcast_addr;
    do{
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if ( sock < 0 ){
            fprintf(stdout , "create socket failed.");
            break;
        }
        
        int yes = 1;
        ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));
        if( ret < 0 ){
            fprintf(stdout, "setsockopt failed. ");
            break;
        }

        memset(&mcast_addr, 0, sizeof(mcast_addr));
        mcast_addr.sin_family = AF_INET;
        mcast_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
        mcast_addr.sin_port = htons(9999);
        
        ret = bind(sock, (struct sockaddr *)&mcast_addr, sizeof(mcast_addr));
        if ( ret < 0 ){
            fprintf(stdout, "bind failed.");
            break;
        }
     
        uint8_t buf[1024] = { 0 };
        int count = 0;
        while(1)
        {
            recvfrom(sock, buf, 1024, 0, NULL, NULL);
            printf("%s\n", buf);
            count += 1;
            if (count > 10){
                break;
            }
        }
        return 0;
    }while(0); 
    if ( sock ){
        close(sock);
    }
    return -1;
}
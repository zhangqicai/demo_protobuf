#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "demo.pb-c.h"

int show_info(Demo__DemoInfo *people){
    int ret = 0;
    int i = 0;
    int j = 0;
    for(i = 0; i < people->n_people; i++){
        Demo__Person *person = people->people[i];
        fprintf(stdout, "id:%u\n", person->id);
        fprintf(stdout, "name:%s\n", person->name);
        fprintf(stdout, "email:%s\n", person->email);
        for(j = 0; j < person->n_phones; j++){
            Demo__Person__PhoneNumber *phone_number = person->phones[j];
            if( phone_number->type == DEMO__PERSON__PHONE_TYPE__MOBILE){
                fprintf(stdout, " Mobile phone : %s\n", phone_number->number);
            }
            else if( phone_number->type == DEMO__PERSON__PHONE_TYPE__HOME){
                fprintf(stdout, " Home phone : %s\n", phone_number->number);
            }
            else if( phone_number->type == DEMO__PERSON__PHONE_TYPE__WORK){
                fprintf(stdout, " Work phone : %s\n", phone_number->number);
            }
            else{
                fprintf(stdout, " Unknow phone : %s\n", phone_number->number);
            }
        }
    }
        
}

int main(int args, char *argv[]){
    
    int sock = 0;
    int ret = 0;
    struct sockaddr_in mcast_addr;
    do{
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if ( sock < 0 ){
            fprintf(stderr, "create socket failed.");
            break;
        }
        
        int yes = 1;
        ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));
        if( ret < 0 ){
            fprintf(stderr, "setsockopt failed. ");
            break;
        }

        memset(&mcast_addr, 0, sizeof(mcast_addr));
        mcast_addr.sin_family = AF_INET;
        mcast_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
        mcast_addr.sin_port = htons(9999);
        
        ret = bind(sock, (struct sockaddr *)&mcast_addr, sizeof(mcast_addr));
        if ( ret < 0 ){
            fprintf(stderr, "bind failed.");
            break;
        }
     
        int len = 0;
        int count = 0;
        uint8_t buf[1024] = { 0 };
        Demo__DemoInfo *people = NULL;
        while(1)
        {
            ret = recvfrom(sock, buf, 1024, 0, NULL, NULL);
            if( ret < 0 ){
                fprintf(stderr, "recvfrom failed.");
            }
            
            len = strnlen(buf, 1024);
            people = demo__demo_info__unpack(NULL, len, buf);
            if( NULL == people ){
                fprintf(stderr, "unpack failed.\n");
            }
            
            show_info(people);
            
            demo__demo_info__free_unpacked(people, NULL);
            people = NULL;

            if (count++ > 10){
                break;
            }
        }
        demo__demo_info__free_unpacked(people, NULL);
        close(sock);
        return 0;
    }while(0); 

    if ( sock ){
        close(sock);
    }
    return -1;
}
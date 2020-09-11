#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "demo.pb-c.h"

int gen_person_info(Demo__Person **people, size_t *n_people, uint32_t count){
    if( NULL == people){
        fprintf(stderr, "input parameter invalied.\n");
        return -1;
    }

    char buf[1024] = { 0 };
    Demo__Person *person = NULL;
    Demo__Person__PhoneNumber *phoneNumber = NULL;
    Demo__Person__PhoneNumber *phoneNumber2 = NULL;
    do{
        person = (Demo__Person *)malloc(sizeof(Demo__Person));
        if( NULL == person){
            fprintf(stderr, "no memory for person. \n");
            break;
        }
        demo__person__init(person);
    
        person->id = count;
        
        sprintf(buf, "zh%u", count);
        person->name = strdup(buf);
        
        sprintf(buf, "%u@c.com", count);
        person->email = strdup(buf);

        person->n_phones = 2;
        person->phones = ( Demo__Person__PhoneNumber **)malloc(person->n_phones * sizeof(Demo__Person__PhoneNumber*));
        if( NULL ==person->phones){
            fprintf(stderr, "no memory for phones. \n");
            break;
        }
    
        phoneNumber = (Demo__Person__PhoneNumber *)malloc(sizeof(Demo__Person__PhoneNumber));
        if( NULL == phoneNumber){
            fprintf(stderr, "no memory for phoneNumber. \n");
            break;
        }
    
        demo__person__phone_number__init(phoneNumber);
        phoneNumber->number = strdup("13766558899");
        phoneNumber->type = DEMO__PERSON__PHONE_TYPE__MOBILE;
        person->phones[0] = phoneNumber;
    
        phoneNumber2 = (Demo__Person__PhoneNumber *)malloc(sizeof(Demo__Person__PhoneNumber));
        if( NULL == phoneNumber2){
            fprintf(stderr, "no memory for phoneNumber. \n");
            break;
        }
    
        demo__person__phone_number__init(phoneNumber2);
        phoneNumber2->number = strdup("2773344");
        phoneNumber2->type = DEMO__PERSON__PHONE_TYPE__WORK;
        person->phones[1] = phoneNumber2;

        *n_people = 1;
        *people = person;
        return 0;
    }while(0);
    if( phoneNumber2 ){
        if( phoneNumber2->number ){
            free(phoneNumber2->number);
        }
        free(phoneNumber2);
    }
    if( phoneNumber ){
        if( phoneNumber->number ){
            free(phoneNumber->number);
        }
        free(phoneNumber);
    }
    if( person ){
        if( person->email ){
            free(person->email);
        }
        if( person->name ){
            free(person->name);
        }
        if( person->phones ){
            free(person->phones);
        }
        free(person);
    }
    return -1;
}

void gen_person_info_relase(Demo__Person **people, size_t n_people){
    if( NULL == people && n_people <= 0){
        fprintf(stderr, "input parameter invailed.\n");
        return;
    }
    int i = 0;
    for(i = 0; i < n_people; i++){
        Demo__Person *person = people[i];
        if( NULL == person ){
            continue;
        }
        if( person->email ){
            free(person->email);
        }
        if( person->name ){
            free(person->name);
        }
        if( person->phones && person->n_phones > 0)
        {
            int j = 0;
            for(j = 0; j < person->n_phones; j++){
                Demo__Person__PhoneNumber *phone_number = person->phones[j];
                if( NULL == phone_number ){
                    continue;
                }
                if( phone_number->number ){
                    free(phone_number->number);
                }
                free(phone_number);
            }
        }
        free(person);
    }
}

void udp_server(int sock, struct sockaddr_in mcast_addr, Demo__DemoInfo *info){
    int ret = 0;
    int len = 0;
    uint8_t *buf = NULL;
    uint32_t count = 0;    
    while(1){

        sleep(1);
        
        ret = gen_person_info(info->people, &info->n_people, count);
        if( ret < 0 ){
            fprintf(stderr, "gen_person_info failed.\n");
            continue;
        }

        len = demo__demo_info__get_packed_size(info);
        if( len < 0 ){
            fprintf(stderr, "get packed size failed.\n");
            continue;
        }

        buf = (uint8_t *)malloc(len);
        if( NULL == buf ){
            fprintf(stderr, "no memory for buf.\n");
            continue;
        }

        ret = demo__demo_info__pack(info, buf);
        if( ret < 0 ){
            fprintf(stderr, "pack info failed.\n");
            free(buf);
            continue;
        }

        ret = sendto(sock, buf, len, 0, (struct sockaddr*)&mcast_addr, sizeof(mcast_addr));
        if( ret < 0 ){
            fprintf(stderr, "sendto failed.\n");
        }
        
        free(buf);
        gen_person_info_relase(info->people, info->n_people);
        printf("c udp server is running %u\n", count++);
    }

}

int main(int args, char *argv[]){
    int ret = 0;
    int sock = 0;
    Demo__DemoInfo *info = NULL;
    do{
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if( sock < 0 ){
            fprintf(stderr, "create socket failed.\n");
            break;
        }

        int yes = 1;
        ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));
        if( ret < 0 ){
            fprintf(stderr, "setsockopt failed.\n");
            break;
        }

        struct sockaddr_in mcast_addr;
        memset(&mcast_addr, 0, sizeof(mcast_addr));
        mcast_addr.sin_port = htons(9999);
        mcast_addr.sin_family = AF_INET;
        mcast_addr.sin_addr.s_addr = inet_addr("255.255.255.255");

        info = (Demo__DemoInfo *)malloc(sizeof(Demo__DemoInfo));
        if( NULL == info ){
            fprintf(stderr, "no memory for info.\n");
            break;
        }

        demo__demo_info__init(info);

        info->people = (Demo__Person **)malloc(sizeof(Demo__Person*));
        if( NULL == info->people ){
            fprintf(stderr, "no memory for info->people");
            break;
        }

        udp_server(sock, mcast_addr, info);

        close(sock);
        return 0;
    }while(0);
    if( sock ){
        close(sock);
    }
    if( info ){
        if( info->people ){
            free(info->people);
        }
        free(info);
    }
    return -1;
}
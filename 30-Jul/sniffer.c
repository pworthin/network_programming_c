#include "helper.h"

void process_packet(int data, unsigned char *buffer);

int main(int argc, char *argv[]){

    disable_echo_of_ctrl_c();
    int sock_raw, data;
    signal(SIGINT, gen_term);
    struct sockaddr addr;
    unsigned char *buffer = (unsigned char *)malloc(BUFFER_MAX);
    socklen_t addrlen = sizeof(addr);

    sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if(sock_raw == -1){

        fprintf(stderr, "\n%sError building socket:%s %s",RED, RESET, strerror(errno));
        stackTrace();
    }

    while(1){

        data = recvfrom(sock_raw, buffer, BUFFER_MAX, 0, &addr, &addrlen);
        if( data == -1){

            fprintf(stderr, "\n%sError receiving data:%s %s", RED, RESET, strerror(errno));
            stackTrace();
        }
        process_packet(data, buffer);
    }

  
}

void process_packet(int data, unsigned char *buffer){

    struct iphdr *ipheader = (struct iphdr*)buffer;
    unsigned short iplen = ipheader->ihl*4;

    struct sockaddr_in source, dest;
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = ipheader->saddr;

    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = ipheader->daddr;

    if(ipheader->protocol == 6){
        struct tcphdr *tcpheader = (struct tcphdr *)(buffer + iplen);
        printf("\nSource address: " GREEN "%s:%u" RESET "\t----\tDestination Address: "\
        GREEN "%s:%u " RESET " ",  inet_ntoa(source.sin_addr), ntohs(tcpheader->source),\
        inet_ntoa(dest.sin_addr), (tcpheader->dest));


    }
    if(ipheader->protocol == 17 ){

        struct udphdr *udpheader = (struct udphdr*)(buffer + iplen);
        printf("\nSource address: " GREEN "%s:%u" RESET "\t----\tDestination Address: "\
        GREEN "%s:%u " RESET " ",  inet_ntoa(source.sin_addr), ntohs(udpheader->source),\
        inet_ntoa(dest.sin_addr), ntohs(udpheader->dest));
    }


  }

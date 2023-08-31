#include "helper.h"

//sniffer

int main (int argc, int *argv[]){

    int fd = 0;
    char buffer[BUFFER_SIZE];
    int s = socket_build(fd, SOCK_RAW, IPPROTO_IP);
    struct sockaddr_in incoming;
    int optval = 1;
    
    if(setsockopt(s, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(optval)) == -1){

        int e = errno;
        fprintf(stderr, RED "\nError setting socket options" RESET, strerror(e) );
        stackTrace();
    }
    while(1){

    ssize_t bytes_recv = recvfrom(s,buffer, BUFFER_SIZE, 0, NULL, NULL);
   
}
}
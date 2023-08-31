#include "helper.h"

int main(int argc, char *argv[]){


    signal(SIGINT, terminate);

    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET_ADDRSTRLEN];
    memset(&hints, 0, sizeof(hints));
    hints.ai_family =AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((status = getaddrinfo(NULL, "6000", &hints, &res)) != 0){

        fprintf(stderr, RED "\nError obtaining address info" RESET "  ", gai_strerror(status));
        stackTrace();
    }

    int server = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(bind(server, res->ai_addr, res->ai_addrlen) == -1){
        int e = errno;
        fprintf(stderr, RED "\nBind Error" RESET "  ", strerror(e));
        stackTrace();
    }
    printf("\nBind successful");
    fflush(stdout);
    if(listen(server, 10) == -1){
        int e = errno;
        fprintf(stderr, RED "\nListening error" RESET "  ", strerror(e));
        stackTrace();
    }
    void *serveraddr;
    p = res;
    struct sockaddr_in *s_addr = (struct sockaddr_in *)p->ai_addr;
    
    serveraddr = &(s_addr->sin_addr);
    inet_ntop(p->ai_family, serveraddr, ipstr,sizeof(ipstr));
    printf("\nListening at %s...", ipstr);

    
} 
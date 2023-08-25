#include "helper.h"
#include "socket_mods.h"


struct multiplex_fd{

    fd_set readfs;
    fd_set writefs;
};

void stackTrace(){

    void *stack[5];
    size_t size = backtrace(stack, sizeof(stack)/sizeof(stack[0]));
    char **symbols = backtrace_symbols(stack, size);
    printf("\nError encountered. Stack trace:\n");
    for(size_t i = 0; i < size; i++){

        printf("[%lu %s\n]", i, symbols[i]);

        free(symbols);
        exit(EXIT_FAILURE);
    }   
}


void multiplex_socket(int fd, struct sockaddr_in* address){

    struct multiplex_fd multiSock;
    struct timeval timeout;

    FD_ZERO(&multiSock.readfs);
    
    int clientSocket;
    timeout.tv_sec = 15;

    int status = select(fd + 1, &multiSock, NULL, NULL, &timeout);

    if(status == -1){

        perror("Select Error");
        perror(errno);
    }
    else if (status == 0){

        printf("\nServer timed out");
        exit(0);
    }
    while(1){
        FD_SET(fd, &multiSock.readfs);
        if(FD_ISSET(fd, &multiSock.readfs)){
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            clientSocket = accept(fd, (struct sockaddr*)&client_addr, &client_len);

        }

    }
}

int main(int argc, char **argv){


    int fd, server;
    signal(SIGINT, terminate);
    signal(SIGSEGV, stackTrace);
    server = socket_build(fd);
    struct sockaddr_in* server_addr = addr_fmt();


}

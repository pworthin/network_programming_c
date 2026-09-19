#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "terminator.h"

#define BUFFER_DEFAULT 4096


int socket_build(void){

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

      int reuse = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
        perror("Setsockopt error");
        close(fd);
        return -1;
    }
    return fd;
}
void directoryTrav(int cliSock, char *buffer, size_t buffer_size){

    struct dirent **directory;
    int n = scandir("/home/kali", &directory, NULL, alphasort);
    if(n < 0){

        perror("Scandir");
        exit(EXIT_FAILURE);
    }

    while(n--){
        snprintf(buffer, buffer_size,"%s\n", directory[n]->d_name);
        send(cliSock, buffer, strlen(buffer),0);
        send(cliSock, "\n", 1, 0);
        free(directory[n]);
    }
    free(directory);
}
struct sockaddr_in* addr_fmt(){

    struct sockaddr_in *addr =
        malloc(sizeof(struct sockaddr_in));

    if (addr == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    memset(addr, 0, sizeof(*addr));

    addr->sin_family = AF_INET;
    addr->sin_port = htons(6000);
    addr->sin_addr.s_addr = htonl(INADDR_ANY);

    return addr;
}

void data_process(int client,  char* ip){
    // Parameter struct sockaddr_in* server_addr was removed for the time being
    time_t now = time(NULL);
    
    struct tm *timeclock =localtime(&now);
    //struct sockaddr server_ip = server_addr;
    char send_buffer[BUFFER_DEFAULT], greeting[BUFFER_DEFAULT];
    snprintf(greeting, sizeof(greeting), "\nConnected with %s. It is now %02d:%02d:%02d", ip, timeclock->tm_hour, timeclock->tm_min, timeclock->tm_sec);
    send(client, greeting, strlen(greeting), 0);
    memset(send_buffer, 0, sizeof(send_buffer));
    directoryTrav(client, send_buffer, sizeof(send_buffer));
    
}



void session_build(int server, struct sockaddr_in* address){
    socklen_t addr_len = sizeof(struct sockaddr_in);
    if (bind(server,(struct sockaddr*)address, addr_len) != 0){
        perror("Bind error");
        printf("Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    int test = listen(server, 5);
    if( test == -1){
        perror("Listening error");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Returning status of %d\n", test);
    }
    printf("Listening for a connection....\n");
    struct sockaddr_in client_addr;
    int client;
    socklen_t client_len; 
    
    
    while(1){
        
        client_len = sizeof(client_addr);
    
        client = accept(server, (struct sockaddr*)&client_addr, &client_len);
       

    if (client == -1){
        if (errno == EINTR && shutdown_requested)
            break;
        perror("Client connection error");
        //exit(EXIT_FAILURE);
        break;
    }
     printf("Connection established with %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
     data_process(client, inet_ntoa(client_addr.sin_addr));

     close(client);
    printf("\rClosing socket....");

    }
    close(server);
    free(address);

    printf("\nServer terminated.\n");

    
    //exit(0);
}



int main(void){

    int server;


    sentinel();

    server = socket_build();
    struct sockaddr_in* server_addr = addr_fmt();
    session_build(server, server_addr);
    tstate_return();

    return 0;

}
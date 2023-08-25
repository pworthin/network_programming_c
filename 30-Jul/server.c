#define _GNU_SOURCE
#include "helper.h"
#include "socket_mods.h"




#define BUFFER_DEFAULT 4096

int sigNum = 0;

void terminate(int sigNum){

    exit(0);
}

int socket_build(int fd){

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

      int reuse = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
        perror("Setsockopt error");
        close(fd);
        return 1;
    }
    return fd;
}
void directoryTrav(int cliSock, char *buffer){

    struct dirent **directory;
    int n = scandir("/home/kali", &directory, NULL, alphasort);
    if(n < 0){

        perror("Scandir");
        exit(EXIT_FAILURE);
    }

    while(n--){
        snprintf(buffer, sizeof(buffer),"%s\n", directory[n]->d_name);
        send(cliSock, buffer, strlen(buffer),0);
        send(cliSock, "\n", 1, 0);
        free(directory[n]);
    }
    free(directory);
}
struct sockaddr_in* addr_fmt(){

    struct sockaddr_in* addr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    
    addr->sin_family = AF_INET;
    addr->sin_port = htons(6000);
    addr->sin_addr.s_addr = inet_addr("192.168.56.112");

    return addr;
}

void data_process(int client, int server, struct sockaddr_in* server_addr, char* ip){
    
    time_t now = time(NULL);
    
    struct tm *timeclock =localtime(&now);
    //struct sockaddr server_ip = server_addr;
    char buffer[BUFFER_DEFAULT], send_buffer[BUFFER_DEFAULT], greeting[BUFFER_DEFAULT];
    ssize_t bytes_recv, sentByte;
    snprintf(greeting, sizeof(send_buffer), "\nConnected with %s. It is now %02d:%02d:%02d", ip, timeclock->tm_hour, timeclock->tm_min, timeclock->tm_sec);
    send(client, greeting, sizeof(greeting), 0);
    memset(send_buffer, 0, sizeof(send_buffer));
    directoryTrav(client, send_buffer);
    
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
        perror("Client connection error");
        exit(EXIT_FAILURE);
    }
     printf("Connection established with %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
     data_process(client, server, address, inet_ntoa(client_addr.sin_addr));

     close(client);
    printf("\rClosing socket....");
    close(client);  
    }
    

       
    
    
    exit(0);
}






int main(int argc, char **argv){

    int fd, server, port;
    
    //const char* ip = argv[1];
    //port = atoi(argv[1]);

    signal(SIGINT, terminate);
    server = socket_build(fd);
    struct sockaddr_in* server_addr = addr_fmt();
    session_build(server, server_addr);

    return 0;

}
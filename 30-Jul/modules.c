#include "helper.h"


int socketQueue[MAX_SOCKETS];
//int num_sockets = 0;
int position = 0;


int socketAdd(int fd){
    
    if(position > MAX_SOCKETS){

        printf("\nSocket #%d: Maximum connections exceeded!", fd);
        fflush(stdout);
        return -1;
    }
    else{
        socketQueue[position] = fd;
        position++;

        return 0;
    }


}

int socket_build(int fd, int type){

  
    fd= socket(AF_INET, type, 0);
    if(fd < 0){
        perror("Error creating socket");
        stackTrace();
        //exit(EXIT_FAILURE);
    }

      int reuse = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
        perror("Setsockopt error");
        close(fd);
        stackTrace();
        //return 1;
    }
    socketAdd(fd);
    return fd;
}



struct sockaddr_in* addr_fmt(char* ip, int port){

    struct sockaddr_in* addr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    int result;
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    //addr->sin_addr.s_addr = inet_addr("192.168.56.112");
    result = inet_pton(AF_INET, ip, &addr->sin_addr);
    if(result == -1)
    {
        fprintf(stderr, "\nInvalid IP address format");
        stackTrace();
    }
    return addr;
}

void terminate(int signNum){

    printf("\rTerminating server upon request");
    fflush(stdout);

    for(int i = 0; i < position; i++){
        close(socketQueue[i]);
    }
    exit(0);

}

void session_build(int server, struct sockaddr_in* address){

    socklen_t addr_len = sizeof(struct sockaddr_in);
    struct sockaddr_in client_addr;
    int client_socket;
    socklen_t client_len = sizeof(client_addr);
    if(bind(server, (struct sockaddr*)address, addr_len) == -1){

        perror("Bind error");
        stackTrace();
    }
    if(listen(server, 5) == -1){

        perror("Listen error");
        stackTrace();

    }
    else{
        printf("\nListening for connections...");

    }
    while(1){

        client_socket = accept(server, (struct sockaddr*)&client_addr, &client_len);

        if(client_socket == -1){
            perror("Client connection error");
            stackTrace();
        }
        
        printf("\nConnection established with %s:%d", inet_ntoa(client_addr.sin_addr),\
        ntohs(client_addr.sin_port));
        
    }
}

/*
void udp_session(int fd, struct sockaddr_in* address)
        {
    
            //struct sockaddr_in *client_addr = addr_fmt(client_ip, client_port);
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(struct sockaddr_in);
            socklen_t addr_len = sizeof(struct sockaddr_in);
            

            char buffer[BUFFER_SIZE], recvbuf[BUFFER_SIZE];
            if(bind(fd, (struct sockaddr*)address, addr_len) == -1){
                int e = errno;
                //perror("\nBind error");
                fprintf(stderr,"\nBind error:%s", strerror(e));
                stackTrace();
            }
            printf("\nServer online -> " YELLOW "%s:%d" RESET " ", inet_ntoa(address->sin_addr), ntohs(address->sin_port));
            memset(buffer, 0, BUFFER_SIZE);
            //memset(client_addr, 0, sizeof(client_addr));

            //Sends connecting user the current directory
            char cwd[1024];
            getcwd(cwd, BUFFER_SIZE);
            printf("\nWaiting for a connection...\n");
            fflush(stdout);
            
            int n = recvfrom(fd, recvbuf, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_len);
            if(n == -1){
                int e = errno;
                fprintf(stderr, "\nClient Socket Error: %s", strerror(e));
                stackTrace();
            }

            char client_ip[INET_ADDRSTRLEN];
            int client_port = ntohs(client_addr.sin_port);
            const char *result = inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
            if(result == NULL){

                int e = errno;
                fprintf(stderr, "\nError converting IP address: %s", strerror(e));
                stackTrace();
            }
            printf("\nReceived a connection from %s:%d\n", client_ip, client_port);
            fflush(stdout);
            
            sprintf(buffer, "\nYou have now connected to" GREEN " %s:%d." RESET "The current directory is: " BLUE, inet_ntoa(address->sin_addr), ntohs(address->sin_port));
            strncat(buffer, cwd, sizeof(buffer) -strlen(buffer) -1);
            sendto(fd, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, client_len);


            struct pollfd fdq[1];
            fdq[0].fd = fd;
            fdq[0].events =POLLIN | POLLOUT;

            while(1){
                memset(buffer, 0, BUFFER_SIZE);
                memset(recvbuf, 0, BUFFER_SIZE);
                int status;
                if((status = poll(fdq,1, -1)) ==-1){
                    
                    perror("Polling error");
                    stackTrace();
                }
                if(status > 0){
                    if(fdq[0].revents & POLLIN){
                recvfrom(fd, recvbuf, strlen(recvbuf), 0, (struct sockaddr*)&client_addr, &client_len);
                    }
                    if(fdq[0].revents & POLLOUT){
                        sendto(fd, buffer, strlen(buffer), 0, (const struct sockaddr*)&client_addr, client_len);
     
                    }
                }

            }
}

*/
void multiplex_session(int fd, struct sockaddr_in* address){

    //struct multiplex_fd mxfd;
    
    fd_set write_set, read_set;
    int maxfd;
    int clientSocket, traffic;
    struct timeval timeout;
    timeout.tv_sec = 180;
    
    setsockopt(fd, SOL_SOCKET,SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
    
    
    FD_ZERO(&read_set);
    FD_SET(fd, &read_set);

    
    socklen_t client_len;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    
    if(bind(fd, (struct sockaddr*)address, addr_len) != 0){

        perror("Bind error");
        stackTrace();
    }
     
        printf("\nBind successful");
        fflush(stdout);
    int test = listen(fd, 10);
    
    if(test != 0)
    {

        perror("Listen error");

       stackTrace();
    }
   
       
        printf("\nWaiting for connections...");
        fflush(stdout);
      ;

    
    while(1){
    FD_ZERO(&write_set);
    FD_SET(fd, &write_set);
        
        
    maxfd = fd;

    traffic = select(maxfd +1, &write_set, NULL, NULL, NULL);

    if(traffic == -1){

        perror("Select fd error");
        stackTrace();

    
    }
        if(FD_ISSET(fd, &write_set)){

            struct sockaddr_in client_addr;
            client_len = sizeof(client_addr);
            clientSocket = accept(fd, (struct sockaddr*)&client_addr, &client_len);
            if(clientSocket == -1){
                
                perror("Client accept error");
                
                
                stackTrace();
                //continue;
            }
            FD_SET(clientSocket, &write_set);

            
            if( socketAdd(clientSocket) == -1){
                //printf("Maximum connections exceeded!");
                close(clientSocket);
                continue;
            }
                if (clientSocket > maxfd){

                maxfd = clientSocket;
            }

            printf("\nConnection established with %s:%d\n", inet_ntoa(client_addr.sin_addr),\
        ntohs(client_addr.sin_port));
            
            data_process(clientSocket, fd, address, inet_ntoa(address->sin_addr));
            sleep(5);
        }
            
    }

}


void data_process(int client, int server, struct sockaddr_in* server_addr, char* ip){
    
    time_t now = time(NULL);
    
    struct tm *timeclock =localtime(&now);
    //struct sockaddr server_ip = server_addr;
     char send_buffer[BUFFER_SIZE], greeting[BUFFER_SIZE];
    //ssize_t bytes_recv, sentByte;
    snprintf(greeting, sizeof(send_buffer), "\nConnected with %s. It is now %02d:%02d:%02d", ip, timeclock->tm_hour, timeclock->tm_min, timeclock->tm_sec);
    send(client, greeting, sizeof(greeting), 0);
    memset(send_buffer, 0, sizeof(send_buffer));
    directoryTrav(client, send_buffer);
    
}


void stackTrace(){

    void *stack[15];
    int size = backtrace(stack, sizeof(stack)/sizeof(stack[0]));
    char **symbols = backtrace_symbols(stack, size);
    printf("\nError encountered. Stack trace:\n");
    for(int i = 0; i < size; i++){

       printf("[%d %s]\n", i, symbols[i]);

       
    }
        free(symbols);
        exit(EXIT_FAILURE);

    }

     


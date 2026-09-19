#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "socket_mods.h"

//This program tests a multiplexing server



int main(int argc, char *argv[]){

    int server;
    server = 0;
    char *ip = argv[1];
    int port = atoi(argv[2]);
    signal(SIGSEGV, stackTrace);
    signal(SIGINT, terminate);
    server = socket_build(server, SOCK_STREAM, 0);
    struct sockaddr_in *serveraddr = addr_fmt(ip, port);
    multiplex_session(server, serveraddr);
    
    return 0;


    
}
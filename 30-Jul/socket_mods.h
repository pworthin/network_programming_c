#ifndef SOCKET_MODS_H
#define SOCKET_MODS_H
#define BUFFER_SIZE 4096
#define MAX_SOCKETS 5
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"


#include "helper.h"

int socket_build(int fd, int type);
void directoryTrav(int cliSock, char *buffer);
struct sockaddr_in* addr_fmt(char* ip, int port);
void terminate(int sigNum);
void session_build(int server, struct sockaddr_in* address);
void stackTrace();
void data_process(int client, int server, struct sockaddr_in* server_addr, char* ip);
void multiplex_session(int fd, struct sockaddr_in* address);
int socketAdd(int fd);
void udp_session(int fd, struct sockaddr_in* address);



// Structs //






// Variables //

extern int socketQueue[MAX_SOCKETS];
extern int position;
#endif
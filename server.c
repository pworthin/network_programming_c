#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>


int main(){

int fd, port;
char buffer[4096] = "Connection established";
struct sockaddr_in server;
struct sockaddr_storage client_addr;
const char *ip = "192.168.56.112";


fd = socket(AF_INET, SOCK_STREAM, 0);

server.sin_port = htons(8050);
server.sin_addr.s_addr = inet_addr(ip);
server.sin_family = AF_INET;

bind(fd, (struct sockaddr*) &server, sizeof(server));
listen(fd, 10);

int client_size = sizeof(client_addr);

int client = accept(fd, (struct sockaddr*) &client_addr, &client_size);

send(client, buffer, sizeof(buffer), 0);

close(fd);

return 0;
}

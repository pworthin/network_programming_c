

#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include "helper.h"

void initialize_server(int fd, struct sockaddr_in* address, socklen_t addr_len);
void wait_for_connection(int fd, struct sockaddr_in* client_addr, socklen_t* client_len, char* client_ip, int* client_port);
void send_welcome_message(int fd, struct sockaddr_in* address, struct sockaddr_in* client_addr, socklen_t client_len);
void handle_communication(int fd, struct sockaddr_in* client_addr, socklen_t client_len);
void udp_session(int fd, struct sockaddr_in* address);

#endif // UDP_SERVER_H

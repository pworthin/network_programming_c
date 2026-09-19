#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "socket_mods.h"
#include "udp_header.h"


int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <IP|any> <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);

    signal(SIGINT, terminate);

    int server = socket_build(SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in *server_addr = addr_fmt(ip, port);

    udp_session(server, server_addr);

    free(server_addr);
    return EXIT_SUCCESS;
}
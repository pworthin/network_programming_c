#include "helper.h"


int main(){

    signal(SIGINT, terminate);
    signal(SIGSEGV, stackTrace);
    int server, port;
    server = 0;
    char *ip = "192.168.56.112";
    port = 6000;
    struct sockaddr_in *addr;
    server = socket_build(server, SOCK_DGRAM);
    
    addr = addr_fmt(ip, port);
    socketAdd(server);

    udp_session(server, addr);

    return 0;
}
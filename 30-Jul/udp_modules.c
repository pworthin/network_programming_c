#include "helper.h"

void initialize_server(int fd, struct sockaddr_in* address, socklen_t addr_len) {
    if (bind(fd, (struct sockaddr*)address, addr_len) == -1) {
        int e = errno;
        fprintf(stderr, "\nBind error:%s", strerror(e));
        stackTrace();
    }
    printf("\nServer online -> " YELLOW "%s:%d" RESET " ", inet_ntoa(address->sin_addr), ntohs(address->sin_port));
}

void wait_for_connection(int fd, struct sockaddr_in* client_addr, socklen_t* client_len, char* client_ip, int* client_port) {
    char recvbuf[BUFFER_SIZE];
    int n = recvfrom(fd, recvbuf, BUFFER_SIZE, 0, (struct sockaddr*)client_addr, client_len);
    if (n == -1) {
        int e = errno;
        fprintf(stderr, "\nClient Socket Error: %s", strerror(e));
        stackTrace();
    }

    const char* result = inet_ntop(AF_INET, &client_addr->sin_addr, client_ip, INET_ADDRSTRLEN);
    if (result == NULL) {
        int e = errno;
        fprintf(stderr, RED "\nError converting IP address:" RESET " %s" , strerror(e));
        stackTrace();
    }
    *client_port = ntohs(client_addr->sin_port);
    printf("\nReceived a connection from %s:%d\n", client_ip, *client_port);
    fflush(stdout);
}

void send_welcome_message(int fd, struct sockaddr_in* address, struct sockaddr_in* client_addr, socklen_t client_len) {
    char buffer[BUFFER_SIZE];
    char cwd[1024];
    getcwd(cwd, BUFFER_SIZE);
    sprintf(buffer, "\nYou have now connected to" GREEN " %s:%d." RESET "The current directory is: " BLUE, inet_ntoa(address->sin_addr), ntohs(address->sin_port));
    strncat(buffer, cwd, sizeof(buffer) - strlen(buffer) - 1);
    sendto(fd, buffer, strlen(buffer), 0, (struct sockaddr*)client_addr, client_len);
}

void handle_communication(int fd, struct sockaddr_in* client_addr, socklen_t client_len) {
    struct pollfd fdq[1];
    char buffer[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];

    fdq[0].fd = fd;
    fdq[0].events = POLLIN | POLLOUT;

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        memset(recvbuf, 0, BUFFER_SIZE);
        int status;
        if ((status = poll(fdq, 1, -1)) == -1) {
            perror("Polling error");
            stackTrace();
        }
        if (status > 0) {
            if (fdq[0].revents & POLLIN) {
                recvfrom(fd, recvbuf, strlen(recvbuf), 0, (struct sockaddr*)client_addr, &client_len);
            }
            if (fdq[0].revents & POLLOUT) {
                sendto(fd, buffer, strlen(buffer), 0, (const struct sockaddr*)client_addr, client_len);
            }
        }
    }
}

void udp_session(int fd, struct sockaddr_in* address) {
    socklen_t addr_len = sizeof(struct sockaddr_in);
    char client_ip[INET_ADDRSTRLEN];
    int client_port;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(struct sockaddr_in);

    initialize_server(fd, address, addr_len);
    memset(&client_addr, 0, sizeof(client_addr));
    printf("\nWaiting for a connection...\n");
    fflush(stdout);
    wait_for_connection(fd, &client_addr, &client_len, client_ip, &client_port);
    send_welcome_message(fd, address, &client_addr, client_len);
    handle_communication(fd, &client_addr, client_len);
}

# Linux Network Programming in C

A collection of network programming exercises and experiments written in C, focusing on low-level socket programming, TCP/UDP communication, packet inspection, and I/O multiplexing.

This repository was originally developed as a hands-on exploration of Linux network programming and has since been cleaned up for reference and demonstration.

## Topics Demonstrated

The project includes examples of:

- TCP socket creation and connection handling
- UDP communication using datagram sockets
- IPv4 address and port handling
- POSIX socket APIs
- Raw sockets
- TCP, UDP, and IP header inspection
- Packet sniffing
- `select()` and `poll()` based I/O multiplexing
- Signal handling
- Socket option configuration
- Filesystem interaction through a network connection
- Dynamic memory and buffer management in C

## Sniffer Project

The `Sniffer Project` directory contains the primary networking experiments.

### TCP Server

`server.c` implements a basic TCP server using the POSIX socket API.

The server:

1. Creates an IPv4 TCP socket.
2. Configures the socket with `SO_REUSEADDR`.
3. Binds to the local system.
4. Listens for incoming connections.
5. Accepts clients.
6. Reports the client's IP address and port.
7. Sends information back to the connected client.

The server binds using `INADDR_ANY`, allowing it to listen on available IPv4 interfaces.

### UDP Server

`udp-server.c` and `udp_modules.c` demonstrate connectionless communication using UDP.

The server address and port are supplied at runtime:

```bash
./udp-server <IP|any> <port>
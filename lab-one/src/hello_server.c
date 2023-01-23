#include "../../lib/util.h"
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFLEN 1500

/**
 * Actually create the socket
 * @return the file descriptor of the server socket
 * @return -1 for failure
 */
int create_socket() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        printf("Error: Creating Socket\n");
        exit(-1);
    }
    return fd;
}

/**
 * Bind socket to port on network interface
 *
 * @param fd the file descriptor of the server socket
 */
void bind_socket(int fd) {
    struct sockaddr_in addr;

    addr.sin_family = AF_INET; // IPv4
    addr.sin_addr.s_addr = INADDR_ANY; // Any available network interface
    addr.sin_port = htons(5000);

    if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        printf("Error: Binding Socket\n");
        exit(-1);
    }
}

/**
 * Start listening for connections
 *
 * @param fd the file descriptor of the server socket
 */
void start_listening(int fd) {
    int backlog = 10;
    if (listen(fd, backlog) == -1) {
        printf("Error: Starting To Listen For Connections\n");
        exit(-1);
    }
}

/**
 * Now start accepting connections from the client
 *
 * @param fd the file descriptor of the server socket
 * @return the file descriptor of the client socket
 * @return -1 for failure
 */
int accept_client(int fd) {
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    int connfd = accept(fd, (struct sockaddr *) &client_address, &client_address_len);
    if (connfd == -1) {
        printf("Error: Client Connection GONE WRONG");
        exit(-1);
    }

    return connfd;
}

int main() {
    int fd = create_socket();
    bind_socket(fd);
    start_listening(fd);
    printf("Listening For Connections\n");
    int connfd = accept_client(fd);

    char buf[BUFLEN + 1];
    buf[BUFLEN] = '\0';
    ssize_t recv_count = recv_all(connfd, buf, BUFLEN);

    if (recv_count >= 0) {
        printf("Data Received: %s\n", buf);
    } else {
        printf("Error: Receiving Data\n");
    }

    close(connfd);
    printf("Client Connection Closed\n");
    close(fd);
    printf("Server Closed\n");

    return 0;
}
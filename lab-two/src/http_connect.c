#include <stdio.h>
#include "../../lib/util.h"
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFLEN 256

struct addrinfo *retrieve_addresses(char *hostname, char *port) {
    struct addrinfo hints;
    struct addrinfo *ai0;

    // https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-getaddrinfo-get-address-information
    // "In the hints structure every member other than ai_flags, ai_family, ai_socktype, and ai_protocol must be zero or a null pointer."
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC; // Unspecified protocol (IPv4 or IPv6 okay)
    hints.ai_socktype = SOCK_STREAM; // Want a TCP socket

    // Perform a DNS lookup. The variable ai0 is set to point to the head
    // of a linked list of struct addrinfo values containing the possible
    // addresses of the server.
    int i;
    if ((i = getaddrinfo(hostname, port, &hints, &ai0)) != 0) {
        printf("Error: unable to lookup IP address: %s", gai_strerror(i));
        exit(-1);
    }

    return ai0;
}

int connect_to_device(struct addrinfo *addresses, char *hostname) {
    struct addrinfo *ai;
    int fd;

    // Iterate over the linked list of results of the DNS lookup, trying to
    // connect to each in turn, breaking out when successfully connected.
    for (ai = addresses; ai != NULL; ai = ai->ai_next) {
        fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (fd == -1) {
            // Unable to create socket, try next address in list
            continue;
        }
        if (connect(fd, ai->ai_addr, ai->ai_addrlen) == -1) {
            // couldn't connect to the address, try next in list
            close(fd);
            continue;
        }
        break; // successfully connected
    }

    if (ai == NULL) {
        printf("Could Not Connect To Any Device At: %s", hostname);
        exit(-1);
    }

    return fd;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Host Name Missing!\n");
        exit(-1);
    } else if (argc < 3) {
        printf("Port Missing\n");
        exit(-1);
    }

    char *hostname = argv[1];
    char *port = argv[2];
    char *http_protocol = "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n";
    char *http_request = malloc(sizeof(char) * (strlen(http_protocol) + strlen(hostname) + 1));
    if (sprintf(http_request, http_protocol, hostname) < 0) {
        exit(-1);
    }

    struct addrinfo *addresses = retrieve_addresses(hostname, port);
    int connfd = connect_to_device(addresses, hostname);
    send_all(connfd, http_request);

    char buf[BUFLEN + 1];
    for (;;) {
        ssize_t recv_count = recv_all(connfd, buf, BUFLEN);
        buf[recv_count] = '\0';

        if (*buf == '\0') {
            break;
        }

        if (recv_count >= 0) {
            printf("%s", buf);
        } else {
            printf("Error: Receiving Data\n");
        }
    }

    close(connfd);
    freeaddrinfo(addresses);
    free(http_request);
    return 0;
}
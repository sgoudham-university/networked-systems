#include "stdlib.h"
#include "string.h"
#include <sys/socket.h>

char *create_str(int n) {
    char *str = malloc(n + 1);
    memset(str, 'a', n);
    str[n] = '\0';
    return str;
}

int recv_all(int fd, char *buf, long size) {
    while (size > 0) {
        ssize_t recvd = recv(fd, buf, size, 0);
        if (recvd < 0) {
            return -1;
        }
        if (recvd == 0)
            break;
        buf += recvd;
        size -= recvd;
    }

    return 0;
}


int send_all(int connfd, char *buf) {
    size_t size = strlen(buf);

    while (size > 0) {
        long sent = send(connfd, buf, size, MSG_NOSIGNAL);
        if (sent == -1) {
            return -1;
        }
        buf += sent;
        size -= sent;
    }

    return 0;
}
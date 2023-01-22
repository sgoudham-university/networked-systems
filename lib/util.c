#include "stdlib.h"
#include "string.h"
#include <sys/socket.h>

int recv_all(int fd, char *buf, long size) {
    while (size > 0) {
        ssize_t recvd = recv(fd, buf, size, 0);
        if (recvd == 0) {
            break;
        }
        if (recvd < 0) {
            return -1;
        }
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
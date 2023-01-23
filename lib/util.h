#include "stdio.h"

/**
 * Wrapper around the normal recv() function.
 * This makes sure that the *buf contains all the bytes sent over by the client.
 *
 * @param fd the file descriptor of the socket
 * @param buf the buffer to put received data into
 * @param size the maximum allocated size of the buffer
 * @return total amount of bytes read
 * @return -1 for failure to read bytes
 */
ssize_t recv_all(int fd, char *buf, long size);

/**
 * Wrapper around the normal send() function.
 * This makes sure that the data within the *buf is transferred over the server.
 *
 * @param connfd the file descriptor of the socket
 * @param buf the buffer containing the bytes to transfer
 * @return 0 for success
 * @return -1 for failure to read bytes
 */
int send_all(int connfd, char *buf);
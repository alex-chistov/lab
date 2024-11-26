#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include "erproc.h"

#define PORT 34543

int main() {
    int fd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(PORT);

    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);
    Connect(fd, (struct sockaddr *)&adr, sizeof adr);

    while (1) {
        char message[256];
        printf("Enter message: ");
        fgets(message, sizeof(message), stdin);

        write(fd, message, strlen(message));

        char buffer[256] = {0};
        ssize_t nread = read(fd, buffer, sizeof(buffer) - 1);

        if (nread <= 0) {
            if (nread == 0) {
                printf("Server closed connection.\n");
            } else {
                perror("Read error");
            }
            break;
        }

        buffer[nread] = '\0';
        printf("Server: %s", buffer);
    }

    close(fd);
    return 0;
}

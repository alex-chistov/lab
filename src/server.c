#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "erproc.h"

#define PORT 34543

void save_to_history(const char *message) {
    FILE *file = fopen("chat_history.txt", "a");
    if (!file) {
        perror("Failed to open chat history file");
        return;
    }
    fprintf(file, "%s\n", message);
    fclose(file);
}

int main() {
    int server = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(PORT);
    adr.sin_addr.s_addr = INADDR_ANY;

    Bind(server, (struct sockaddr *)&adr, sizeof adr);
    Listen(server, 3);

    printf("Server is running and waiting for connections...\n");

    socklen_t addrlen = sizeof adr;
    while (1) {
        int client = Accept(server, (struct sockaddr *)&adr, &addrlen);
        printf("Client connected.\n");

        while (1) {
            char buffer[256] = {0};
            ssize_t nread = read(client, buffer, sizeof(buffer) - 1);

            if (nread <= 0) {
                if (nread == 0) {
                    printf("Client disconnected.\n");
                } else {
                    perror("Read error");
                }
                break;
            }

            buffer[nread] = '\0';
            printf("Client: %s", buffer);
            save_to_history(buffer);

            char response[256];
            printf("Enter response: ");
            fgets(response, sizeof(response), stdin);
            write(client, response, strlen(response));
            save_to_history(response);
        }

        close(client);
    }

    close(server);
    return 0;
}

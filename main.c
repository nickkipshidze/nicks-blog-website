#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include "views.h"

int main(int argc, char *argv[]) {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in serverAddress = {
        .sin_family = AF_INET,
        .sin_port = htons(8000),
        .sin_addr.s_addr = INADDR_ANY
    };

    int bindStatus = bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    printf("[+] Bind status: %d\n", bindStatus);
    listen(serverSocket, 32);

    while (true) {
        int connection = accept(serverSocket, NULL, NULL);

        char request[2048];
        recv(connection, request, sizeof(request), 0);

        size_t responseLength = -1;
        char *response = routeRequest(request, &responseLength);

        if (response != NULL && responseLength != -1) {
            ssize_t sent = send(connection, response, responseLength, 0);
            printf(" |  Responded %d bytes\n", (int)sent);
            free(response);
        } else {
            printf("[-] Not responding\n");
        }

        shutdown(connection, SHUT_WR);
    }

    close(serverSocket);
    return 0;
}

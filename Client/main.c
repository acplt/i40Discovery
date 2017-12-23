//
// Created by Jérôme Lenssen on 20.12.17.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int authenticate(int socket, int* ds_key) {
    // first build packet. Then send

    return 1;
}


int main(int argc, char* argv[]) {
    char* ip_adress;
    char* port;
    int* ds_key;

    if(argc == 3) {
        ip_adress = (char*)malloc(sizeof(argv[1]));
        memcpy(ip_adress, argv[1], sizeof(argv[1]));
        port = (char*)malloc(sizeof(argv[2]));
        memcpy(port, argv[2], sizeof(argv[2]));
    }
    else {
        fprintf(stderr, "error: usage <ip> <port>");
    }

    printf("connecting to: ip::%s, port::%s", ip_adress, port);

    int sock_fd;
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, port, &hints, &res);

    // server info
    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr(ip_adress);
    server.sin_family = AF_INET;
    server.sin_port = htons( atoi(port) );

    // create socket
    if(!(sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol))) {
        fprintf(stderr, "could not create socket");
        return -1;
    }

    // connect to server
    if (connect(sock_fd , (struct sockaddr *)&server , sizeof(server)) == -1) {
        fprintf(stderr, "could not connect to server");
        return -1;
    }

    for(;;) {
        // first authenticate and request DS_KEY
        authenticate(sock_fd, ds_key);
        break;
    }
    free(ip_adress);
    free(port);

    close(sock_fd);

    return 0;
}
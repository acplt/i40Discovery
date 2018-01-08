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

#include "types.h"
#include "../network.h"

#define OFFSET 5
#define BUFFER_SIZE 1024


int main(int argc, char* argv[]) {
    char* ip_adress;
    char* port;

    if(argc == 3) {
        ip_adress = malloc(sizeof(argv[1]) + OFFSET);
        strcpy(ip_adress, argv[1]);
        port = malloc(sizeof(argv[2]) + OFFSET);
        strcpy(port, argv[2]);
    }
    else {
        fprintf(stderr, "error: usage <ip> <port>");
        return -1;
    }

    printf("connecting to:\n ip: %s\n port: %s\n", ip_adress, port);

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

    char* my_ip = "127.0.0.1#";
    char* my_cert = "foo#";
    // fill request struct
    request_header* request_cert = get_request_header(my_ip, my_cert, GET_CERTIFICATE_KESEC_Request);
    request_datagram* packet = malloc(sizeof(request_datagram));

    packet->requestHeader request_cert;
    packet->data = "$";

    serialize_info* info = serialize_request_packet(packet);
    // write to socket
    write(sock_fd, info->data, info->length);

    char* data = malloc(1024*sizeof(char));
    data = receive_data(sock_fd);


    free(ip_adress);
    free(port);

    close(sock_fd);

    return 0;
}
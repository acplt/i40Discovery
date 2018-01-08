//
// Created by Jérôme Lenssen on 06.01.18.
//

#ifndef DISTRIBUTEDDISCOVERYSERVER_NETWORK_H
#define DISTRIBUTEDDISCOVERYSERVER_NETWORK_H

#include <mysql.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "ds_database.h"
#include "types.h"

#define MAX_DATA 2048
#define CHUNK 1024
#define MAXIMUM_PACKET_LENGTH 10000

/*** typedefs ***/
// request header
typedef struct request_header{
    time_t time;
    uint64_t request_handle;
    uint64_t time_duration;
    char* endpoint;
    char* certificate;
    // ADDITIONAL_HEADER reserved
} request_header;
// response header
typedef struct response_header{
    time_t time;
    uint64_t request_handle;
    uint64_t status_code;
    // ADDITIONAL_HEADER reserved
} response_header;
// datagram
typedef struct request_datagram {
    request_header  requestHeader;
    char*           data;
} request_datagram;
// response datagram
typedef struct response_datagram {
    request_header  responseHeader;
    char*           data;
} response_datagram;
// thread data
typedef struct thread_data{
    int socketfd;
    MYSQL* handle;
    struct sockaddr_in client_info;
} thread_data;
// serialize info
typedef struct serialize_info {
    char* data;
    int length;
} serialize_info;

// thread function to handle incoming connections
void* connection_handler(void* arg);
// receive data and write it to char pointer (Reads maximum of 10000 bytes)
char* receive_data(int socket);
// parse received data and write it to datagram struct
int check_certificate(char* certificate);

int AUT_KESEC(request_datagram* packet, thread_data* thr_data);
int RELEASE_KEY_KESEC(request_datagram* packet, thread_data* thr_data);
int GET_CERTIFICATE_KESEC(request_datagram* packet, thread_data* thr_data);
int GET_KES_KESEC(request_datagram* packet, thread_data* thr_data);

response_header* get_response_header(int request_type, int status_code);
request_header* get_request_header(int request_type, const char* ip, const char* cert);

serialize_info* serialize_response_packet(response_datagram* packet);
serialize_info* serialize_request_packet(request_datagram* packet);

request_datagram* parse_request_data(char* data)
response_datagram* parse_response_data(char* data)

#endif //DISTRIBUTEDDISCOVERYSERVER_NETWORK_H

//
// Created by Jérôme Lenssen on 06.01.18.
//

#include "network.h"


response_header* get_response_header(int request_type, int status_code) {
    response_header* tmp = malloc(sizeof(response_header));
    if(tmp == NULL) {
        fprintf(stderr, "could not allocate response header!");
    } else {
        tmp->time = time(0);
        tmp->request_handle = request_type;
        tmp->status_code = status_code;
    }
    return tmp;
}

request_header* get_request_header(int request_type, const char* ip, const char* cert) {
    request_header *tmp = malloc(sizeof(request_header));
    if(tmp == NULL) {
        fprintf(stderr, "could not allocate response header!");
    } else {
        tmp->time = time(0);
        tmp->request_handle = request_type;
        tmp->time_duration = 2000;
        tmp->endpoint = malloc(strlen(ip));
        memcpy(tmp->endpoint, ip, strlen(ip));
        tmp->certificate = malloc(strlen(cert));
        memcpy(tmp->certificate, cert, strlen(cert));
    }
    return tmp;
}

serialize_info* serialize_response_packet(response_datagram* packet) {
    char* buffer = malloc(sizeof(char)*1024);
    if(buffer == NULL) {
        fprintf(stderr, "could not allocate buffer!");
        return -1;
    }
    int offset = 0;

    memcpy(&buffer[offset], packet->responseHeader.time, sizeof(packet->responseHeader.time));
    offset += sizeof(packet->responseHeader.time);
    memcpy(&buffer[offset], packet->responseHeader.request_handle, sizeof(packet->responseHeader.request_handle));
    offset += sizeof(packet->responseHeader.request_handle);
    memcpy(&buffer[offset], packet->responseHeader.time_duration, sizeof(packet->responseHeader.time_duration));
    offset += sizeof(packet->responseHeader.time_duration);
    memcpy(&buffer[offset], packet->data, strlen(packet->data));
    offset += strlen(packet->data);

    serialize_info* info = malloc(sizeof(serialize_info));
    info->data = malloc(offset);
    memcpy(info->data, buffer, offset);
    info->length = offset;

    return info;
}

serialize_info* serialize_request_packet(request_datagram* packet) {
    // serialize struct (write to buffer and write to socket)
    char* buffer = malloc(sizeof(char)*1024);
    if(buffer == NULL) {
        fprintf(stderr, "could not allocate buffer!");
        return -1;
    }
    int offset = 0;

    memcpy(&buffer[offset], &packet->requestHeader.time, sizeof(packet->requestHeader.time));
    offset += sizeof(packet->requestHeader.time);
    memcpy(&buffer[offset], &packet->requestHeader.request_handle, sizeof(packet->requestHeader.request_handle));
    offset += sizeof(packet->requestHeader.request_handle);
    memcpy(&buffer[offset], &packet->requestHeader.time_duration, sizeof(packet->requestHeader.time_duration));
    offset += sizeof(packet->requestHeader.time_duration);
    memcpy(&buffer[offset], packet->requestHeader.endpoint, strlen(packet->requestHeader.endpoint));
    offset += strlen(packet->requestHeader.endpoint);
    memcpy(&buffer[offset], packet->requestHeader.certificate, strlen(packet->requestHeader.certificate));
    offset += strlen(packet->requestHeader.certificate);

    serialize_info* info = malloc(sizeof(serialize_info));
    info->data = malloc(offset);
    memcpy(info->data, buffer, offset);
    info->length = offset;

    return info;
}

int GET_CERTIFICATE_KESEC(request_datagram* packet, thread_data* thr_data) {
    // next check time duration
    if(time(0) - packet->requestHeader.time > packet->requestHeader.time_duration) {
        fprintf(stderr, "timeout!\n");
        close(thr_data->socketfd);
        pthread_exit(NULL);
    }

    response_header* response_h = get_response_header(GET_CERTIFICATE_KESEC_Request, DS_OK);
    response_datagram* packet = malloc(sizeof(response_datagram));
    if(packet == NULL) {
        fprintf(stderr, "could not create packet!\n");
        close(thr_data->socketfd);
        pthread_exit(NULL);
    }

    packet->responseHeader = *response_h;
    packet->data = "foo cert$";

    serialize_info* info = serialize_response_packet(packet);

    if(write(thr_data->socketfd, info->data, info->length) == -1) {
        return -1;
    };

    return 1;
}

int AUT_KESEC(request_datagram* packet, thread_data* thr_data) {
    // next check time duration
    if(time(0) - packet->requestHeader.time > packet->requestHeader.time_duration) {
        fprintf(stderr, "timeout!\n");
        close(thr_data->socketfd);
        pthread_exit(NULL);
    }


    return 1;
}

int RELEASE_KEY_KESEC(request_datagram* packet, thread_data* thr_data) {
    // next check time duration
    if(time(0) - packet->requestHeader.time > packet->requestHeader.time_duration) {
        fprintf(stderr, "timeout!\n");
        close(thr_data->socketfd);
        pthread_exit(NULL);
    }


    return 1;
}

int GET_KES_KESEC(request_datagram* packet, thread_data* thr_data) {
    // next check time duration
    if(time(0) - packet->requestHeader.time > packet->requestHeader.time_duration) {
        fprintf(stderr, "timeout!\n");
        close(thr_data->socketfd);
        pthread_exit(NULL);
    }


    return 1;
}

void* connection_handler(void *arg) {
    // get data
    thread_data* thr_data = (thread_data*)arg;
    // display client id for debugging
    fprintf(stdout, "connected to: %s\n", inet_ntoa(thr_data->client_info.sin_addr));
    // if bad request let's abort
    char* data;
    if((data = receive_data(thr_data->socketfd)) == NULL) {
        fprintf(stderr, "packet could not be read\n");
        close(thr_data->socketfd);
        pthread_exit(NULL);
    }
    fprintf(stdout, "received packet\n");
    // get datagram from raw stream
    request_datagram* packet = parse_request_data(data);

    switch(packet->requestHeader.request_handle) {
        case GET_CERTIFICATE_KESEC_Request: GET_CERTIFICATE_KESEC(packet, thr_data); break;
        case AUT_KESEC_Request: AUT_KESEC(packet, thr_data); break;
        case RELEASE_KEY_KESEC_Request: RELEASE_KEY_KESEC(packet, thr_data); break;
        case GET_KES_KESEC_Request: GET_KES_KESEC(packet, thr_data); break;
        default: break;
    }


    close(thr_data->socketfd);
    pthread_exit(NULL);
}

char* receive_data(int socket) {
    // buffer for reading
    char* data;
    data = malloc(sizeof(char)*MAX_DATA);
    // bytes read and number of total bytes read
    int len, total_len;
    len = total_len = 0;
    // receive data
    while(1) {
        // check if packet is to large
        if(total_len >= MAXIMUM_PACKET_LENGTH) {
            fprintf(stderr, "maximum packet length. Abort");
            return NULL;
        }
        if(total_len + CHUNK > MAX_DATA) {
            realloc(data, CHUNK);
        }
        len = read(socket, data+total_len, CHUNK);
        total_len += len;
        if(data[total_len-1] == '$') {
            break;
        }
    }
    return data;
}

request_datagram* parse_request_data(char* data) {
    request_header* request_h = malloc(sizeof(request_header));
    int offset, count;
    offset = count = 0;

    memcpy(&request_h->time, data, sizeof(time_t));
    offset += sizeof(time_t);
    memcpy(&request_h->request_handle, data+offset, sizeof(uint64_t));
    offset += sizeof(uint64_t);
    memcpy(&request_h->time_duration, data+offset, sizeof(uint64_t));
    offset += sizeof(uint64_t);
    // find length of string endpoint '#'
    while(data[offset+count] != '#') { count++; }
    request_h->endpoint = malloc(sizeof(char)*count);
    memcpy(request_h->endpoint, data+offset, count);
    offset += count+1;
    count = 0;
    // find length of string cert with '$'
    while(data[offset+count] != '$') { count++; }
    request_h->certificate = malloc(sizeof(char)*count);
    memcpy(request_h->certificate, data+offset, count);

    request_datagram* packet = malloc(sizeof(request_datagram));
    packet->requestHeader = *request_h;

    return packet;
}

response_datagram* parse_response_data(char* data) {
    return NULL;
}

int check_certificate(char* certificate) {
    return 1;
}



/*int AUT_KESEC(datagram* packet, thread_data* thr_data) {
    if(check_certificate(packet->data)) {
        // build string representing values
        char* query_values;
        strcat(query_values, packet->requestHeader.endpoint);
        // insert values into database
        insert_into_table(thr_data->handle, query_values);
        // send response with ds_key
        response_header* responseHeader;
        responseHeader->request_handle = packet->requestHeader.request_handle;
        responseHeader->time = time(NULL);
        // check if time duration is okay
        // TODO: is this ms??
        if(difftime(responseHeader->time, packet->requestHeader.time) > (double)packet->requestHeader.time_duration) {
            responseHeader->status_code = DS_ABORT;
        } else {
            responseHeader->status_code = DS_OK;
        }
        // build message string
        char* msg;
        // TODO: build message string...
        return 1;
    }
    else {
        fprintf(stderr, "bad certificate\n");
        return 0;
    }
}

int RELEASE_KEY_KESEC(datagram* packet, thread_data* thr_data) {
    // TODO: release key
    return 1;
}*/
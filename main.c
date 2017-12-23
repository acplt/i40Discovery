#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "DiscoveryServer/types.h"
#include "ds_database.h"

// TODO: doxygen documentation
// TODO: config file
// TODO: memory check

// define global variables
int sig_flag;

/******* defines (MAX_THREAD not used at the moment) *******/
#define MAX_DATA 2048
#define CHUNK 512
#define MAX_THREADS 8

/******* typedefs *******/
// thread data
typedef struct thread_data{
    int socketfd;
    MYSQL* handle;
    struct sockaddr_in client_info;
} thread_data;

/******* helper functions (will be moved to separate header) *******/
void skip_comment(FILE* file) {
    while(fgetc(file) == '#') {
        fscanf(file, "%*[^\n]\n", NULL);
    }
}

int get_config(const char* config_file, configuration* config) {
    FILE* file;
    if((file = fopen(config_file, "r")) == NULL) {
        fprintf(stderr, "error: could not open config file");
        return 0;
    }
    else {
        char* tmp = (char*)malloc(sizeof(char*)*100);
        // check for comment
        skip_comment(file);
        while(fgetc(file) != '=') {}
        strcpy(config->ip_security,strtok(fgets(tmp, 200, file),"\n"));
        skip_comment(file);
        while(fgetc(file) != '=') {}
        config->port_security = atoi(fgets(tmp, 200, file));
        skip_comment(file);
        while(fgetc(file) != '=') {}
        config->ip_registration = strtok(fgets(tmp, 200, file), "\n");
        skip_comment(file);
        while(fgetc(file) != '=') {}
        fscanf(file, tmp);
        config->port_registration = atoi(tmp);
        while(fgetc(file) != '=') {}
        config->ip_resolution = strtok(fgets(tmp, 200, file),"\n");
        skip_comment(file);
        while(fgetc(file) != '=') {}
        fscanf(file, tmp);
        config->port_resolution = atoi(tmp);
        while(fgetc(file) != '=') {}
        config->ip_resolution = strtok(fgets(tmp, 200, file),"\n");
        skip_comment(file);
        while(fgetc(file) != '=') {}
        fscanf(file, tmp);
        config->port_search = atoi(tmp);
        skip_comment(file);
        while(fgetc(file) != '=') {}
        config->ip_resolution = strtok(fgets(tmp, 200, file),"\n");
        skip_comment(file);
        while(fgetc(file) != '=') {}
        fscanf(file, tmp);
        config->port_database = atoi(tmp);
        skip_comment(file);
        while(fgetc(file) != '=') {}
        config->ip_resolution = strtok(fgets(tmp, 200, file),"\n");
        skip_comment(file);
        while(fgetc(file) != '=') {}
        config->ip_resolution = fgets(tmp, 200, file);
        fclose(file);
        return 1;
    }
}

void signal_handler(int sig) {
    sig_flag = 1;
}

datagram* parse_data(char* data) {
    datagram* packet = (datagram*)malloc(sizeof(datagram));
    int len = 0;
    int count = 0;
    uint64_t* tmp;
    // first four bytes to time_t
    memcpy(tmp, data+len, 4);
    len += 4;
    packet->requestHeader.time = *(time_t*)time;
    // next request handle
    memcpy(tmp, data+len, 4);
    packet->requestHeader.request_handle = *tmp;
    len += 4;
    // time_duration
    memcpy(tmp, data+len, 4);
    packet->requestHeader.time_duration = *tmp;
    len += 4;
    // now check length of string of endpoint
    count = 0;
    while(data[len] != '#') { count++; }
    memcpy(packet->requestHeader.endpoint, data+len, count);
    len+=count+1;
    // now we only need to put the rest into data without '$'
    count = 0;
    while(data[len] != '$') { count++; }
    memcpy(packet->data, data+len, count);

    return packet;
}

char* receive_data(int socket) {
    // buffer for reading 
    char* data;
    data = (char*)calloc(MAX_DATA, sizeof(char));
    // bytes read and number of total bytes read
    int len, total_len;
    len = total_len = 0;
    // receive data
    while(1) {
        if(total_len + CHUNK > MAX_DATA) {
            realloc(data, CHUNK);
        }
        len = recv(socket, data+total_len, CHUNK, 0);
        total_len += len;
        if(data[total_len] == '$') {
            break;
        }
    }
    return data;
}

int check_certificate(char* certificate) {
    return 1;
}

int AUT_KESEC(datagram* packet, thread_data* thr_data) {
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
}

void *thread_function(void *arg) {
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
    // get datagram from raw stream
    datagram* packet = parse_data(data);

    switch(packet->requestHeader.request_handle) {
        case AUT_KESEC_Request: AUT_KESEC(packet, thr_data); break;
        case RELEASE_KEY_KESEC_Request: RELEASE_KEY_KESEC(packet, thr_data); break;
        default: break;
    }

    close(thr_data->socketfd);
    pthread_exit(NULL);
}

int shutdown_server(MYSQL* handle, int socket) {
    // close socket
    if(close(socket) == -1) {
        fprintf(stderr, "socket could not be closed\n");
        return -1;
    }
    // free and close handle
    mysql_close(handle);
    return 1;
}

int main(int argc, char* argv[]) {
    // get config file and save it in configuration struct
    const char* config_file;
    configuration* config = malloc(sizeof(configuration));

    // check for command line arguments
    if(argc == 2) {
        config_file = (char*)malloc(sizeof(argv[1]));
        strcpy(config_file, argv[1]);
    }
    else {
        fprintf(stderr, "usage: ./sec <config_file>\n");
        return -1;
    }

    // read config file
    get_config(config_file, config);

    // init sig_flag to false. Check sig_flag in while loop to stop program
    sig_flag = 0;

    // register signal handler
    signal(SIGINT, signal_handler);

    // create a handle for the database
    MYSQL* handle = mysql_init(NULL);

    if(handle == NULL) {
        fprintf(stderr, "%s\n", mysql_error(handle));
        return 0;
    }
    // connect to database
    if(!connect_to_database(config->ip_database, config->user_database, config->passw_database, handle)) {
        fprintf(stderr, "could not connect to database\n");
        return -1;
    }
    fprintf(stdout, "connected to database\n");

    // we need to choose correct database
    if(mysql_query(handle, "USE test;")) {
        fprintf(stderr, "%s\n", mysql_error(handle));
        mysql_close(handle);
        return -1;
    }
    fprintf(stdout, "selected database\n");

    // do the networking stuff
    int sockfd;
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, config->port_security, &hints, &res);

    // create socket
    if(!(sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol))) {
        fprintf(stderr, "could not create socket\n");
        return -1;
    }
    // bind socket to specific port
    if(bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        fprintf(stderr, "failed to bind\n");
        return -1;
    }
    // listen to incoming connections
    // TODO: is MAX_THREAD good idea?
    if(listen(sockfd, MAX_THREADS) == -1) {
        fprintf(stderr, "listen failed");
        return -1;
    }
    fprintf(stdout, "server is up... waiting for connections...\n");

    // accept incoming connection (one thread per connection)
    struct sockaddr_in client;
    socklen_t client_legnth = sizeof(client);
    while(1) {
        // check if we want to shutdown server
        if(sig_flag) {
            shutdown_server(handle, sockfd);
            return -1;
        }
        int new_socketfd;
        new_socketfd = accept(sockfd, (struct sockaddr* )&client, &client_legnth);
        // if socket could not be created, close connection to database and close socket
        // TODO: eig. nicht notwendig. Hat client halt Pech.
        if (new_socketfd == -1) {
            fprintf(stderr, "failed to create new socket\n");
            shutdown_server(handle, sockfd);
            return -1;
        }
        else {
            // assemble thread_data
            thread_data* thr_data = (thread_data*)malloc(sizeof(thread_data));
            thr_data->socketfd = new_socketfd;
            thr_data->handle = handle;
            thr_data->client_info = client;
            // create thread
            pthread_t thread_id;
            pthread_create(&thread_id, NULL, thread_function, thr_data);
        }
    }
}
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>
#include <stdio.h>

#include "network.h"
#include "ds_database.h"
#include "configuration.h"

// define global variables
int sig_flag;

/******* defines (MAX_THREAD not used at the moment) *******/
#define MAX_THREADS 8

/******* helper functions (will be moved to separate header) *******/
void signal_handler(int sig) {
    sig_flag = 1;
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
    char* config_file;
    configuration* config = malloc(sizeof(configuration));
    MYSQL* handle;

    if(config == NULL) {
        fprintf(stderr, "could not allocate memory for configuration settings");
        return -1;
    }

    // check for command line arguments
    if(argc == 2) {
        // +5 for \0
        config_file = malloc(strlen(argv[1])+5);
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

    // initialize database handle
    handle = mysql_init(NULL);
    if(handle == NULL) {
        fprintf(stderr, "%s\n", mysql_error(handle));
        return -1;
    } else {
        fprintf(stdout, "initialized database handle");
    }

    // connect to database
    if(connect_to_database(config->ip_database, config->user_database, config->passw_database, handle) == -1) { return -1; }

    // select database to use
    if(select_database(handle, config->database) == -1) { return -1; }


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
            pthread_create(&thread_id, NULL, connection_handler, thr_data);
        }
    }
}
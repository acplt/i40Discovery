#include <iostream>
#include <string>
#include <mysql.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <signal.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdlib.h>
#include "DiscoveryServer/services.h"

// TODO: doxygen documentation
// TODO: config file
// TODO: memory check

using std::cerr;
using std::cout;
using std::string;
using std::endl;
using std::to_string;

// define global variables
bool sig_flag;

/******* defines (MAX_THREAD not used at the moment) *******/
#define MAX_DATA 2048
#define CHUNK 512
#define MAX_THREADS 8

/******* typedefs *******/
// thread data
typedef struct thread_data{
    int socketfd;
    MYSQL* handle;
    sockaddr_in client_info;
} thread_data;
// request header
typedef struct request_header{
    time_t time;
    uint64_t request_handle;
    uint64_t time_duration;
    char* endpoint;
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
typedef struct datagram {
    request_header  requestHeader;
    char*           data;
} datagram;
// response datagram

/******* helper functions (will be moved to separate header) *******/
void signal_handler(int sig) {
    sig_flag = true;
}

// TODO: table needs to be variable
/// wrapper to insert data into table tester
/// @param handle MYSQL structure to handle database
/// @param data String holding values for insertion "val1, val2, val3, ..."
/// @return true if query could be executed
bool insert_into_table(MYSQL* handle, const char* data) {
    // build query
    string query = "INSERT INTO tester VALUES (";
    query += string(data);
    query +=");";
    // execute query
    if(mysql_query(handle, query.c_str())) {
        cerr << mysql_error(handle) << endl;
        mysql_close(handle);
        return false;
    }
    return true;
}

// TODO: possible to select database
// in the future it should be possible to select database
bool show_table(MYSQL* handle) {
    // save result
    MYSQL_RES *result;

    if(mysql_query(handle, "SELECT * FROM tester;")) {
        cerr << mysql_error(handle) << endl;
        mysql_close(handle);
        return false;
    }

    result = mysql_store_result(handle);
    cout << "rows: " << result->row_count << endl;

    int number_of_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    while((row = mysql_fetch_row(result))) {
        for(int i = 0; i < number_of_fields; i++) {
            cout << row[i] << " ";
        }
        cout << endl;
    }
    mysql_free_result(result);
    return true;
}

bool connect_to_database(string host, string user, string passw, MYSQL* handle) {
    if(mysql_real_connect(handle, host.c_str(), user.c_str(), passw.c_str(),
                          NULL, 3306, NULL, 0) == NULL) {
        cerr << mysql_error(handle) << endl;
        mysql_close(handle);
        return false;
    }
    return true;
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
    // new request header
    request_header req_h;
    // bytes read and number of total bytes read
    int len, total_len;
    len = total_len = 0;
    // receive data
    while(true) {
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

bool check_certificate(char* certificate) {
    return true;
}

bool AUT_KESEC(datagram* packet, thread_data* thr_data) {
    if(check_certificate(packet->data)) {
        // TODO: generate with mysql hash?
        long ds_key = random();
        // build string representing values
        string query_values;
        query_values += string(packet->requestHeader.endpoint) + ", ";
        query_values += to_string(ds_key);
        // insert values into database
        insert_into_table(thr_data->handle, query_values.c_str());
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
        string msg;
        // TODO: build message string...
        return true;
    }
    else {
        cout << "bad certificate" << endl;
        return false;
    }
}

bool RELEASE_KEY_KESEC(datagram* packet, thread_data* thr_data) {
    // TODO: release key
    return true;
}

void *thread_function(void *arg) {
    // get data
    thread_data* thr_data = (thread_data*)arg;
    // display client id for debugging
    cout << "connected to: " << inet_ntoa(thr_data->client_info.sin_addr) << endl;
    // if bad request let's abort
    char* data;
    if((data = receive_data(thr_data->socketfd)) == NULL) {
        cout << "packet could not be read" << endl;
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
    /* new database entry with insert
    insert_into_table(handle, thread_buffer);*/
}

int shutdown_server(MYSQL* handle, int socket) {
    // close socket
    if(close(socket) == -1) {
        cerr << "socket could not be closed" << endl;
        return -1;
    }
    // free and close handle
    mysql_close(handle);
    return 1;
}

int main(int argc, char* argv[]) {
    // save command line arguments
    string host, user, passw, port;

    // check for command line arguments
    if(argc == 5) {
        host = string(argv[1]);
        user = string(argv[2]);
        passw = string(argv[3]);
        port = string(argv[4]);
    }
    else {
        cerr << "usage: ./sec <host> <user> <password> <port>" << endl;
        return -1;
    }

    // init sig_flag to false. Check sig_flag in while loop to stop program
    sig_flag = false;

    // register signal handler
    signal(SIGINT, signal_handler);

    // create a handle for the database
    MYSQL* handle = mysql_init(NULL);

    if(handle == NULL) {
        cout << mysql_error(handle) << endl;
        return false;
    }
    // connect to database
    if(!connect_to_database(host, user, passw, handle)) {
        cerr << "could not connect to database" << endl;
        return -1;
    }
    cout << "connected to database..." << endl;

    // we need to choose correct database
    if(mysql_query(handle, "USE test;")) {
        cerr << mysql_error(handle) << endl;
        mysql_close(handle);
        return -1;
    }
    cout << "selected test database..." << endl;

    // do the networking stuff
    int sockfd;
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, port.c_str(), &hints, &res);

    // create socket
    if(!(sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol))) {
        cerr << "could not create socket" << endl;
        return -1;
    }
    // bind socket to specific port
    if(bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        cout << "could not bind to port" << endl;
        return -1;
    }
    // listen to incoming connections
    // TODO: is MAX_THREAD good idea?
    if(listen(sockfd, MAX_THREADS) == -1) {
        cout << "listen failed" << endl;
        return -1;
    }
    cout << "server is up... waiting for connections..." << endl;
    
    // accept incoming connection (one thread per connection)
    sockaddr_in client;
    socklen_t client_legnth = sizeof(client);
    while(true) {
        // check if we want to shutdown server
        if(sig_flag) {
            shutdown_server(handle, sockfd);
            return -1;
        }
        int new_socketfd;
        new_socketfd = accept(sockfd, (sockaddr* )&client, &client_legnth);
        // if socket could not be created, close connection to database and close socket
        // TODO: eig. nicht notwendig. Hat client halt Pech.
        if (new_socketfd == -1) {
            cout << "failed to create new socket" << endl;
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
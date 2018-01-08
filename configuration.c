//
// Created by Jérôme Lenssen on 04.01.18.
//

#include <stdlib.h>
#include <string.h>
#include "configuration.h"

char buffer[1024];

char* get_config_string(FILE* file) {
    char* tmp;
    skip_comment(file);
    tmp = malloc(sizeof(char)*100);
    if(tmp == NULL) {
        fprintf(stderr, "could not allocate buffer in get_config_string!");
    } else {
        // TODO: not working at the moment
        if(fgets(buffer, 100, file) == NULL) {
            fprintf(stderr, "missing data in config file! adjust discovery.config");
            return -1;
        } else {
            strcpy(tmp, strtok(buffer, "\n"));
        }
    }
    return tmp;
}

void skip_comment(FILE* file) {
    while(fgetc(file) == '#') {
        fscanf(file, "%*[^\n]\n", NULL);
    }
    fseek(file, -1, SEEK_CUR);
}

int get_config(const char* config_file, configuration* config) {
    FILE* file;
    if((file = fopen(config_file, "r")) == NULL) {
        fprintf(stderr, "error: could not open config file");
        return -1;
    }
    else {
        // read ip address security
        config->ip_security = get_config_string(file);
        // read port number security
        config->port_security = get_config_string(file);
        // read ip address registration
        config->ip_registration = get_config_string(file);
        // read port number registration
        config->port_registration = atoi(get_config_string(file));
        // read ip address resolution
        config->ip_resolution = get_config_string(file);
        // read port number resolution
        config->port_resolution = atoi(get_config_string(file));
        // read ip address search
        config->ip_search = get_config_string(file);
        // read port number search
        config->port_search = atoi(get_config_string(file));
        // read ip address database
        config->ip_database = get_config_string(file);
        // read port database
        config->port_database = atoi(get_config_string(file));
        // read user name
        config->user_database = get_config_string(file);
        // read database password
        config->passw_database = get_config_string(file);
        // read which database should be use
        config->database = get_config_string(file);
        // read which table should be used for authentication
        config->database_table = get_config_string(file);
        fclose(file);
        return 1;
    }
}

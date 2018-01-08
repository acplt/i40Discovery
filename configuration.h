//
// Created by Jérôme Lenssen on 04.01.18.
//

#ifndef DISTRIBUTEDDISCOVERYSERVER_CONFIGURATION_H
#define DISTRIBUTEDDISCOVERYSERVER_CONFIGURATION_H

#include <stdio.h>

// holds important config data such as ip addresses and port numbers
typedef struct configuration {
    char*   ip_security;
    char*     port_security;
    char*   ip_registration;
    int     port_registration;
    char*   ip_resolution;
    int     port_resolution;
    char*   ip_search;
    int     port_search;
    char*   ip_database;
    int     port_database;
    char*   user_database;
    char*   passw_database;
    char*   database;
    char*   database_table;
} configuration;

// skip line containing '#' at the beginning
void skip_comment(FILE* file);
// fill configuration struct with data from config_file
int get_config(const char* config_file, configuration* config);

#endif //DISTRIBUTEDDISCOVERYSERVER_CONFIGURATION_H

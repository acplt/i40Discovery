//
// Created by Jérôme Lenssen on 21.12.17.
//

#include <mysql.h>
#include <stdio.h>
#include <string.h>

#ifndef DISTRIBUTEDDISCOVERYSERVER_DS_DATABASE_H
#define DISTRIBUTEDDISCOVERYSERVER_DS_DATABASE_H

int connect_to_database(char* host, char* user, char* passw, MYSQL* handle);
int show_table(MYSQL* handle);
int insert_into_table(MYSQL* handle, const char* data);

#endif //DISTRIBUTEDDISCOVERYSERVER_DS_DATABASE_H

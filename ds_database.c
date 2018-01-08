//
// Created by Jérôme Lenssen on 21.12.17.
//
#include "ds_database.h"

int connect_to_database(char* host, char* user, char* passw, MYSQL* handle) {
    if(mysql_real_connect(handle, host, user, passw,
                          NULL, 3306, NULL, 0) == NULL) {
        fprintf(stdout, "%s\n", mysql_error(handle));
        fprintf(stderr, "could not connect to database\n");
        mysql_close(handle);
        return -1;
    } else {
        fprintf(stdout, "connected to database\n");
        return 1;
    }
}

int select_database(MYSQL* handle, char* database) {
    // TODO: check database string size
    char command[30] = "USE ";
    if(mysql_query(handle, strcat(command, database))) {
        fprintf(stderr, "%s\n", mysql_error(handle));
        mysql_close(handle);
        fprintf(stderr, "could not select database");
        return -1;
    } else {
        fprintf(stdout, "selected database %s\n", database);
        return 1;
    }
}

int show_table(MYSQL* handle) {
    // save result
    MYSQL_RES *result;

    if(mysql_query(handle, "SELECT * FROM tester;")) {
        fprintf(stderr, "%s\n", mysql_error(handle));
        mysql_close(handle);
        return 0;
    }

    result = mysql_store_result(handle);
    fprintf(stdout, "rows: %s\n", result->row_count);

    int number_of_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    while((row = mysql_fetch_row(result))) {
        for(int i = 0; i < number_of_fields; i++) {
            fprintf(stdout, "%s ", row[i]);
        }
        fprintf(stdout, "\n");
    }
    mysql_free_result(result);
    return 1;
}

// TODO: table needs to be variable
/// wrapper to insert data into table tester
/// @param handle MYSQL structure to handle database
/// @param data String holding values for insertion "val1, val2, val3, ..."
/// @return true if query could be executed
int insert_into_table(MYSQL* handle, const char* data, const char* table) {
    // build query
    // INSERT INTO table VALUES ( dat1, dat2, dat3 );
    char* query = "INSERT INTO ";
    strcat(query, table);
    strcat(query, " VALUES (");
    strcat(query, data);
    strcat(query, ");");
    // execute query
    if(mysql_query(handle, query)) {
        fprintf(stderr, "%s\n", mysql_error(handle));
        mysql_close(handle);
        return -1;
    }
    return 1;
}
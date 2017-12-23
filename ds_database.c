//
// Created by Jérôme Lenssen on 21.12.17.
//
#include "ds_database.h"

int connect_to_database(char* host, char* user, char* passw, MYSQL* handle) {
    if(mysql_real_connect(handle, host, user, passw,
                          NULL, 3306, NULL, 0) == NULL) {
        fprintf(stdout, "%s\n", mysql_error(handle));
        mysql_close(handle);
        return 0;
    }
    return 1;
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
int insert_into_table(MYSQL* handle, const char* data) {
    // build query
    char* query = "INSERT INTO tester VALUES (";
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
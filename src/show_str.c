#include <stdio.h>

#include "sqlite3/sqlite3.h"

int main(void) {
    // the sql we will turn in to a prepared statement
    char *sql = "SELECT id, name, age, email FROM students WHERE id = ?1;";
    sqlite3 *db;                        // pointer to our db
    sqlite3_stmt *pstmt;                // prepared statements corresponding to sql
    const unsigned char *name, *email;  // text columns from our queries
    int id, age;                        // int columns from our queries
    // char *zErrMsg = 0;
    int rc;  // return code from sqlite library

    // 1 open the database
    rc = sqlite3_open_v2("./data-samples/task007.db", &db, SQLITE_OPEN_READONLY, NULL);
    if (rc) {
        sqlite3_close_v2(db);
        rc = sqlite3_open_v2("../data-samples/task007.db", &db, SQLITE_OPEN_READONLY, NULL);
    }
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close_v2(db);
        return (1);
    }

    // 2 create a prepared statement
    rc = sqlite3_prepare_v3(db, sql, -1, 0, &pstmt, NULL);
    if (rc) {
        fprintf(stderr, "Couldn't prepare sql statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return (1);
    }

    // 3 bind the ?1 in the prepared statement
    // to our text we passed into the program
    rc = sqlite3_bind_text(pstmt, 1, "7", -1, NULL);
    if (rc) {
        fprintf(stderr, "Couldn't bind to prepared sql stmt: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return (1);
    }

    // 4 fetch columns from our query
    while (sqlite3_step(pstmt) == SQLITE_ROW) {
        id = sqlite3_column_int(pstmt, 0);
        name = sqlite3_column_text(pstmt, 1);
        age = sqlite3_column_int(pstmt, 2);
        email = sqlite3_column_text(pstmt, 3);
        printf("%d %s %d %s\n", id, name, age, email);
    }

    // 5 close the prepared statement
    sqlite3_finalize(pstmt);

    // 6 close the database
    sqlite3_close_v2(db);
    return 0;
}
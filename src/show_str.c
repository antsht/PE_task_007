#include <stdio.h>

#include "sqlite3/sqlite3.h"

int main(void) {
    sqlite3 *db;
    int rc;

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

    char *sql = "SELECT id, name, age, email FROM students WHERE id = ?1;";
    sqlite3_stmt *pstmt;
    rc = sqlite3_prepare_v3(db, sql, -1, 0, &pstmt, NULL);
    if (rc) {
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return (1);
    }

    rc = sqlite3_bind_text(pstmt, 1, "7", -1, NULL);
    if (rc) {
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return (1);
    }

    while (sqlite3_step(pstmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(pstmt, 0);
        const unsigned char *name = sqlite3_column_text(pstmt, 1);
        int age = sqlite3_column_int(pstmt, 2);
        const unsigned char *email = sqlite3_column_text(pstmt, 3);
        printf("%d %s %d %s\n", id, name, age, email);
    }

    sqlite3_finalize(pstmt);
    sqlite3_close_v2(db);
    return 0;
}
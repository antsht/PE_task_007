#include "db_layer.h"

ErrorCode db_open(sqlite3 **db) {
    int rc = 0;
    rc = sqlite3_open_v2("./data-samples/task007.db", db, SQLITE_OPEN_READWRITE, NULL);
    if (rc) {
        sqlite3_close_v2(*db);
        rc = sqlite3_open_v2("../data-samples/task007.db", db, SQLITE_OPEN_READWRITE, NULL);
    }
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
        sqlite3_close_v2(*db);
        return IO_ERROR;
    }
    return OK;
}

ErrorCode db_close(sqlite3 *db) {
    sqlite3_close_v2(db);
    return OK;
}
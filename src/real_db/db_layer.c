#include "db_layer.h"

ErrorCode db_open(sqlite3 **db) {
    int return_code = 0;
    return_code = sqlite3_open_v2("./data-samples/task007.db", db, SQLITE_OPEN_READWRITE, NULL);
    if (return_code) {
        sqlite3_close_v2(*db);
        return_code = sqlite3_open_v2("../data-samples/task007.db", db, SQLITE_OPEN_READWRITE, NULL);
    }
    if (return_code) {
        log_message2("Can't open database: %s\n", sqlite3_errmsg(*db));
        sqlite3_close_v2(*db);
        return IO_ERROR;
    }
    return OK;
}

ErrorCode db_close(sqlite3 *db) {
    sqlite3_close_v2(db);
    return OK;
}
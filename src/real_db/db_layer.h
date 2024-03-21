#ifndef DB_LAYER_H
#define DB_LATER_H
#include <stdarg.h>
#include <stddef.h>

#include "../common/errors.h"
#include "../sqlite3/sqlite3.h"

ErrorCode db_open(sqlite3 **db);

ErrorCode db_close(sqlite3 *db);
#endif
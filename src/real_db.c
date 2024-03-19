#include "real_db.h"

int main(void) {
    // the sql we will turn in to a prepared statement
    sqlite3 *db = NULL;  // pointer to our db

    // 1 open the database
    try(db_open(&db));
    print_student(get_student(db, 7));
    // 6 close the database
    try(db_close(db));

    close_logger();
    return 0;
}

#include "real_db/ui.h"

int main(void) {
    sqlite3 *db = NULL;
    try(db_open(&db));

    try(main_menu_loop(db));

    try(db_close(db));
    close_logger();
    return 0;
}

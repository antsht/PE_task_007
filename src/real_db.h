#ifndef REAL_DB_H
#define REAL_DB_H
#include <stdio.h>

#include "common/errors.h"
#include "common/logger.h"
#include "db_dal/db_layer.h"
#include "db_dal/students_record.h"

#define BUFFER 254

ErrorCode get_command(char *command);
ErrorCode check_command(char *command);
ErrorCode main_menu_loop(sqlite3 *db);
ErrorCode get_id(int *id);
ErrorCode get_new_student(student_t *student);
#endif
#include "students_record.h"

#include <stdio.h>

student_t get_student(sqlite3 *db, int id) {
    student_t student = {0, "", 0, ""};
    sqlite3_stmt *pstmt;  // prepared statements corresponding to sql
    int rc;               // return code from sqlite library
    char *sql = "SELECT id, name, age, email FROM students WHERE id = ?1;";
    // 2 create a prepared statement
    rc = sqlite3_prepare_v3(db, sql, -1, 0, &pstmt, NULL);
    if (rc) {
        fprintf(stderr, "Couldn't prepare sql statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return student;
    }
    char id_param[10] = {0};
    sprintf(id_param, "%d", id);
    // 3 bind the ?1 in the prepared statement
    // to our text we passed into the program
    rc = sqlite3_bind_text(pstmt, 1, id_param, -1, NULL);
    if (rc) {
        fprintf(stderr, "Couldn't bind to prepared sql stmt: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return student;
    }

    // 4 fetch columns from our query
    while (sqlite3_step(pstmt) == SQLITE_ROW) {
        student.id = sqlite3_column_int(pstmt, 0);
        strcpy(student.name, (const char *)sqlite3_column_text(pstmt, 1));
        student.age = sqlite3_column_int(pstmt, 2);
        strcpy(student.email, (const char *)sqlite3_column_text(pstmt, 3));
    }

    // 5 close the prepared statement
    sqlite3_finalize(pstmt);
    return student;
}

void print_student(student_t student) {
    printf("id: %d\n", student.id);
    printf("name: %s\n", student.name);
    printf("age: %d\n", student.age);
    printf("email: %s\n", student.email);
}
#include "students_record.h"

#include <stdio.h>

student_t get_student(sqlite3 *db, int id) {
    student_t student = {-1, "", 0, ""};
    sqlite3_stmt *pstmt;  // prepared statements corresponding to sql
    int rc;               // return code from sqlite library
    char *sql = "SELECT id, name, age, email FROM students WHERE id = ?1;";

    rc = sqlite3_prepare_v3(db, sql, -1, 0, &pstmt, NULL);
    if (rc) {
        fprintf(stderr, "Couldn't prepare sql statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return student;
    }

    // bind the ?1 in the prepared statement
    rc = sqlite3_bind_int(pstmt, 1, id);
    if (rc) {
        fprintf(stderr, "Couldn't bind to prepared sql stmt: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return student;
    }

    // fetch columns from our query
    while (sqlite3_step(pstmt) == SQLITE_ROW) {
        student.id = sqlite3_column_int(pstmt, 0);
        strcpy(student.name, (const char *)sqlite3_column_text(pstmt, 1));
        student.age = sqlite3_column_int(pstmt, 2);
        strcpy(student.email, (const char *)sqlite3_column_text(pstmt, 3));
    }

    // close the prepared statement
    sqlite3_finalize(pstmt);
    return student;
}

void delete_student(sqlite3 *db, int id) {
    sqlite3_stmt *pstmt;  // prepared statements corresponding to sql
    int rc;               // return code from sqlite library
    char *sql = "DELETE FROM students WHERE id = ?1;";

    rc = sqlite3_prepare_v3(db, sql, -1, 0, &pstmt, NULL);
    if (rc) {
        fprintf(stderr, "Couldn't prepare sql statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return;
    }
    char id_param[10] = {0};
    sprintf(id_param, "%d", id);

    // bind the ?1 in the prepared statement
    rc = sqlite3_bind_text(pstmt, 1, id_param, -1, NULL);
    if (rc) {
        fprintf(stderr, "Couldn't bind to prepared sql stmt: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return;
    }

    /* Execute SQL statement */
    sqlite3_step(pstmt);

    // close the prepared statement
    sqlite3_finalize(pstmt);
}

void add_student(sqlite3 *db, student_t *student) {
    sqlite3_stmt *pstmt;  // prepared statements corresponding to sql
    int rc;               // return code from sqlite library
    char *sql = "INSERT INTO students (name, age, email) VALUES (?1, ?2, ?3);";

    rc = sqlite3_prepare_v3(db, sql, -1, 0, &pstmt, NULL);
    if (rc) {
        fprintf(stderr, "Couldn't prepare sql statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return;
    }

    // bind the ?1 in the prepared statement
    rc = sqlite3_bind_text(pstmt, 1, student->name, -1, NULL);
    if (rc) {
        fprintf(stderr, "Couldn't bind to prepared sql stmt: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return;
    }
    // bind the ?2 in the prepared statement
    rc = sqlite3_bind_int(pstmt, 2, student->age);
    if (rc) {
        fprintf(stderr, "Couldn't bind to prepared sql stmt: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return;
    }
    // bind the ?3 in the prepared statement
    rc = sqlite3_bind_text(pstmt, 3, student->email, -1, NULL);
    if (rc) {
        fprintf(stderr, "Couldn't bind to prepared sql stmt: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return;
    }

    /* Execute SQL statement */
    sqlite3_step(pstmt);

    // close the prepared statement
    sqlite3_finalize(pstmt);
}

void print_all_students(sqlite3 *db) {
    student_t student = {-1, "", 0, ""};
    sqlite3_stmt *pstmt;  // prepared statements corresponding to sql
    int rc;               // return code from sqlite library
    char *sql = "SELECT id, name, age, email FROM students ORDER BY id;";

    rc = sqlite3_prepare_v3(db, sql, -1, 0, &pstmt, NULL);
    if (rc) {
        fprintf(stderr, "Couldn't prepare sql statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(pstmt);
        sqlite3_close_v2(db);
        return;
    }

    // fetch columns from our query
    while (sqlite3_step(pstmt) == SQLITE_ROW) {
        if (sqlite3_column_text(pstmt, 0)) student.id = sqlite3_column_int(pstmt, 0);
        if (sqlite3_column_text(pstmt, 1)) strcpy(student.name, (const char *)sqlite3_column_text(pstmt, 1));
        if (sqlite3_column_text(pstmt, 2)) student.age = sqlite3_column_int(pstmt, 2);
        if (sqlite3_column_text(pstmt, 3)) strcpy(student.email, (const char *)sqlite3_column_text(pstmt, 3));
        print_student(&student);
    }

    // close the prepared statement
    sqlite3_finalize(pstmt);
    return;
}

ErrorCode print_student(student_t *student) {
    if (!student) return NO_DATA;
    if (student->id < 0) return NO_DATA;
    printf("%d ", student->id);
    printf("%s ", student->name);
    printf("%d ", student->age);
    printf("%s\n", student->email);
    return OK;
}
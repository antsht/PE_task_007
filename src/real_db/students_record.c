#include "students_record.h"

#include <stdio.h>

student_t get_student(sqlite3 *db, int id) {
    student_t student = {-1, "", 0, ""};
    sqlite3_stmt *prepared_statement;
    int return_code;
    char *sql = "SELECT id, name, age, email FROM students WHERE id = ?1;";

    return_code = sqlite3_prepare_v3(db, sql, -1, 0, &prepared_statement, NULL);
    if (return_code) {
        log_message2("Couldn't prepare sql statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(prepared_statement);
        sqlite3_close_v2(db);
        return student;
    }

    return_code = sqlite3_bind_int(prepared_statement, 1, id);
    if (return_code) {
        log_message2("Couldn't bind to prepared sql stmt: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(prepared_statement);
        sqlite3_close_v2(db);
        return student;
    }

    while (sqlite3_step(prepared_statement) == SQLITE_ROW) {
        student.id = sqlite3_column_int(prepared_statement, 0);
        strcpy(student.name, (const char *)sqlite3_column_text(prepared_statement, 1));
        student.age = sqlite3_column_int(prepared_statement, 2);
        strcpy(student.email, (const char *)sqlite3_column_text(prepared_statement, 3));
    }

    sqlite3_finalize(prepared_statement);
    return student;
}

void delete_student(sqlite3 *db, int id) {
    sqlite3_stmt *prepared_statement;
    int return_code;
    char *sql = "DELETE FROM students WHERE id = ?1;";

    return_code = sqlite3_prepare_v3(db, sql, -1, 0, &prepared_statement, NULL);
    if (return_code) {
        log_message2("Couldn't prepare sql statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(prepared_statement);
        sqlite3_close_v2(db);
        return;
    }
    char id_param[10] = {0};
    sprintf(id_param, "%d", id);

    return_code = sqlite3_bind_text(prepared_statement, 1, id_param, -1, NULL);
    if (return_code) {
        log_message2("Couldn't bind to prepared sql stmt: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(prepared_statement);
        sqlite3_close_v2(db);
        return;
    }

    sqlite3_step(prepared_statement);

    sqlite3_finalize(prepared_statement);
}

void add_student(sqlite3 *db, student_t *student) {
    sqlite3_stmt *prepared_statement;
    int return_code;
    char *sql = "INSERT INTO students (name, age, email) VALUES (?1, ?2, ?3);";

    return_code = sqlite3_prepare_v3(db, sql, -1, 0, &prepared_statement, NULL);
    if (return_code) {
        log_message2("Couldn't prepare sql statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(prepared_statement);
        sqlite3_close_v2(db);
        return;
    }

    return_code = sqlite3_bind_text(prepared_statement, 1, student->name, -1, NULL);
    if (return_code) {
        log_message2("Couldn't bind to prepared sql stmt: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(prepared_statement);
        sqlite3_close_v2(db);
        return;
    }

    return_code = sqlite3_bind_int(prepared_statement, 2, student->age);
    if (return_code) {
        log_message2("Couldn't bind to prepared sql stmt: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(prepared_statement);
        sqlite3_close_v2(db);
        return;
    }

    return_code = sqlite3_bind_text(prepared_statement, 3, student->email, -1, NULL);
    if (return_code) {
        log_message2("Couldn't bind to prepared sql stmt: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(prepared_statement);
        sqlite3_close_v2(db);
        return;
    }

    sqlite3_step(prepared_statement);

    sqlite3_finalize(prepared_statement);
}

void print_all_students(sqlite3 *db) {
    student_t student = {-1, "", 0, ""};
    sqlite3_stmt *prepared_statement;
    int return_code;
    char *sql = "SELECT id, name, age, email FROM students ORDER BY id;";

    return_code = sqlite3_prepare_v3(db, sql, -1, 0, &prepared_statement, NULL);
    if (return_code) {
        log_message2("Couldn't prepare sql statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(prepared_statement);
        sqlite3_close_v2(db);
        return;
    }

    while (sqlite3_step(prepared_statement) == SQLITE_ROW) {
        if (sqlite3_column_text(prepared_statement, 0))
            student.id = sqlite3_column_int(prepared_statement, 0);
        if (sqlite3_column_text(prepared_statement, 1))
            strcpy(student.name, (const char *)sqlite3_column_text(prepared_statement, 1));
        if (sqlite3_column_text(prepared_statement, 2))
            student.age = sqlite3_column_int(prepared_statement, 2);
        if (sqlite3_column_text(prepared_statement, 3))
            strcpy(student.email, (const char *)sqlite3_column_text(prepared_statement, 3));
        print_student(&student);
    }

    sqlite3_finalize(prepared_statement);
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
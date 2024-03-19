#ifndef STUDENTS_RECORD_H
#define STUDENTS_RECORD_H
#include <string.h>

#include "../sqlite3/sqlite3.h"
#define TEXT_FIELD_LENGTH 128

typedef struct {
    int id;
    char name[TEXT_FIELD_LENGTH + 1];
    int age;
    char email[TEXT_FIELD_LENGTH + 1];
} student_t;

student_t get_student(sqlite3 *db, int id);
void print_student(student_t student);
void get_all_students(sqlite3 *db );
void print_all_students();

#endif
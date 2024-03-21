#include "ui.h"

ErrorCode check_command(char *command) {
    if (strcmp(command, "SHOW") == 0 || strcmp(command, "SHOWALL") == 0 || strcmp(command, "ADD") == 0 ||
        strcmp(command, "REMOVE") == 0 || strcmp(command, "EXIT") == 0)
        return OK;
    return INVALID_COMMAND;
}

ErrorCode get_command(char *command) {
    fgets(command, INPUT_BUFFER_SIZE - 1, stdin);
    int len = strlen(command);
    if (command[len - 1] == '\n') command[len - 1] = '\0';
    return check_command(command);
}

ErrorCode main_menu_loop(sqlite3 *db) {
    int stop = 0;
    ErrorCode error = OK;

    while (!stop) {
        char command[INPUT_BUFFER_SIZE] = {0};

        try(get_command(command));

        if (strcmp(command, "SHOW") == 0) {
            int id = 0;
            try(get_id(&id));
            student_t student = get_student(db, id);
            try(print_student(&student));
        }

        if (strcmp(command, "SHOWALL") == 0) {
            print_all_students(db);
        }

        if (strcmp(command, "ADD") == 0) {
            student_t student = {0, "", 0, ""};
            get_new_student(&student);
            add_student(db, &student);
        }

        if (strcmp(command, "REMOVE") == 0) {
            int id = 0;
            try(get_id(&id));
            delete_student(db, id);
        }
        if (strcmp(command, "EXIT") == 0) {
            stop = 1;
        }
    }
    return error;
}

ErrorCode get_id(int *id) {
    if (scanf("%d", id) != 1 || *id < 0) return INVALID_INPUT;
    getchar();
    return OK;
}

ErrorCode get_new_student(student_t *student) {
    char name[TEXT_FIELD_LENGTH + 1] = {0};
    char email[TEXT_FIELD_LENGTH + 1] = {0};
    int age = 0;
    char input_string[INPUT_BUFFER_SIZE + 1] = {0};
    fgets(input_string, INPUT_BUFFER_SIZE, stdin);
    int len = strlen(input_string);
    if (input_string[len - 1] == '\n') input_string[len - 1] = '\0';
    char *token = strtok(input_string, " ");
    if (token == NULL) return INVALID_INPUT;
    while (token != NULL) {
        strcat(name, token);
        strcat(name, " ");
        token = strtok(NULL, " ");
        if (sscanf(token, "%d", &age) == 1) {
            len = strlen(name);
            name[len - 1] = '\0';
            break;
        }
    }
    token = strtok(NULL, " ");
    if (token != NULL) {
        strcpy(email, token);
    }
    student->id = -1;
    strcpy(student->name, name);
    student->age = age;
    strcpy(student->email, email);
    return OK;
}
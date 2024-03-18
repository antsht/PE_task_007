#include "logger.h"

static FILE *plog_file = NULL;

void init_logger(void) {
    plog_file = fopen("log.txt", "a");
    if (plog_file == NULL) {
        puckxit();
    }
    fprintf(plog_file, "-------------");
}

void log_message(const char *message) {
    if (plog_file == NULL) {
        init_logger();
    }
    if (plog_file != NULL) fprintf(plog_file, "%s\n", message);
}

void close_logger(void) {
    if (plog_file != NULL) {
        fclose(plog_file);
    }
    plog_file = NULL;
}

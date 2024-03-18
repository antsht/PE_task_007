#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 4096

int main(void) {
    char str[MAX_STR_LEN];
    fgets(str, MAX_STR_LEN - 1, stdin);
    char *current_space = strchr(str, ' ');

    if (current_space != NULL) {
        char replacement = ' ';
        scanf("%c", &replacement);
        while (current_space != NULL && replacement != ' ') {
            *current_space = replacement;
            current_space = strchr(current_space, ' ');
        }
    }

    int len = strlen(str);
    if (str[len - 1] == '\n') str[len - 1] = '\0';

    printf("%s", str);
    return 0;
}
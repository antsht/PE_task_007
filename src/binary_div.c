#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 4096

int main(void) {
    char str[MAX_STR_LEN];
    fgets(str, MAX_STR_LEN - 1, stdin);
    int len = strlen(str);
    if (str[len - 1] == '\n') str[len - 1] = '\0';
    while (len / 2 < len) {
        printf("%s", str);
        if (len % 2 + len / 2 < len) {
            printf("\n");
            len = len % 2 + len / 2;
        } else {
            len = len / 2;
        }
        str[len] = '\0';
    }

    return 0;
}
#include <regex.h>
#include <stdio.h>
#include <string.h>

int main() {
    regex_t regex;
    const char* cregex = "^[ab]|[a]$";
    int a = regcomp(&regex, cregex, 0);
    if (a != 0) {
        printf("error\n");
    }
    char cline[10] = {0};
    scanf("%s", cline);
    //cline[strlen(cline) - 1] = '\0';
    int result = regexec(&regex, cline, 0, NULL, 0);
    printf("result -> %d\n", result);
    return 0;
}

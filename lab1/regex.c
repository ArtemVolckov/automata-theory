#include <regex.h>
#include "config.h"

// Previous variant of regex: "^[[:alnum:]./]+[[:blank:]][[:alnum:][:blank:]]*[[:alnum:]]$"
// regcomp with REG_EXTENDED flag is required

#define BUF_SIZE 256 

// Format: match|nomatch "input_string"
void print_status_and_str(regex_t* regex, const char* cline) {
    if (regexec(regex, cline, 0, NULL, 0))  
        printf("nomatch \"%s\"\n", cline);
    else 
        printf("match   \"%s\"\n", cline);
}

// Format: input_string (required for output_parser.c)
void print_matching_str(regex_t* regex, const char* cline) {
    if (!regexec(regex, cline, 0, NULL, 0))  
        printf("%s\n", cline);
}

int main(int argc, const char* argv[]) {
    regex_t regex;
    const char* cregex = "^[[:alnum:]./][[:alnum:]./]*[[:blank:]][[:alnum:][:blank:]]*[[:alnum:]]$";
    char buf[BUF_SIZE + 1] = {0};
    void (*print_function)(regex_t*, const char*) = &print_status_and_str;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [-c | -collect]\n", *argv);
        return 1;
    } 
    if (argc == 2) {
        if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-collect") != 0) {
            fprintf(stderr, "Error: Unknown flag '%s'. Use -c or -collect.\n", argv[1]);
            return 1;
        }
        print_function = &print_matching_str;
    } 
    if (regcomp(&regex, cregex, 0)) {
        fprintf(stderr, "Error: Regular expression compilation failed\n");
        return 1;
    }
    while (fgets(buf, BUF_SIZE, stdin)) {
        size_t str_len = strlen(buf);

        if (buf[str_len - 1] == '\n')
            buf[str_len - 1] = '\0';
        print_function(&regex, buf);
    }
    regfree(&regex);
    return 0;
}

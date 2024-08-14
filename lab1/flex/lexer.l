%{
#include "../config.h"

double total_time_spent = 0.0;

int is_correct;
size_t counter = 0; 
char buf[BUF_SIZE] = {0};

struct timespec start, end;

// Format: match|nomatch "input_string"
void print_status_and_str(const char* str, int is_correct) {
    if (is_correct == 0)  
        printf("nomatch \"%s\"\n", str);
    else 
        printf("match   \"%s\"\n", str);
}

// Format: input_string (required for output_parser.c)
void print_matching_str(const char* str, int is_correct) {
    if (is_correct == 1)  
        printf("%s\n", str);
}

void (*print_function)(const char*, int) = &print_status_and_str;
%}

%%

\n {
    clock_gettime(CLOCK_MONOTONIC, &end);
    total_time_spent += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    buf[counter] = '\0';
    print_function(buf, is_correct);
    counter = 0;
    is_correct = 0;
    clock_gettime(CLOCK_MONOTONIC, &start); 
}

^[[:alnum:]./][[:alnum:]./]*[[:blank:]][[:alnum:][:blank:]]*[[:alnum:]]$ {
    is_correct = 1;
    strncpy(buf, yytext, BUF_SIZE);
    counter = strlen(buf); 
}

. { 
    if (counter != BUF_SIZE - 1) {
        buf[counter] = yytext[0];
        counter++;
    } 
}

%%

int main(int argc, char* argv[]) {
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
    clock_gettime(CLOCK_MONOTONIC, &start); 
    yylex();
    clock_gettime(CLOCK_MONOTONIC, &end);
    total_time_spent += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Total time spent using flex: %.9lf seconds\n", total_time_spent);
    yylex_destroy();
    return 0;
}

#include "SmcRecognizer.h"
#include "../config.h"

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

int main(int argc, const char* argv[]) {
    SmcRecognizer smc_recognizer;
    SmcRecognizer_Init(&smc_recognizer);
    char buf[BUF_SIZE] = {0};
    void (*print_function)(const char*, int) = &print_status_and_str;

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
    while (fgets(buf, BUF_SIZE, stdin)) {
        size_t str_len = strlen(buf);

        if (buf[str_len - 1] == '\n')
            buf[str_len - 1] = '\0';
        check_str(&smc_recognizer, buf);
        print_function(buf, smc_recognizer.is_correct);
        SmcRecognizerContext_reset(&smc_recognizer._fsm);    
    }
    return 0;
}

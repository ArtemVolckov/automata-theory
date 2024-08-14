#include "SmcRecognizer.h"
#include "../config.h"

double total_time_spent = 0.0;

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
    struct timespec start, end;

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

        if (buf[str_len - 1] == '\n') {
            buf[str_len - 1] = '\0';
        }
        clock_gettime(CLOCK_MONOTONIC, &start);
        check_str(&smc_recognizer, buf);
        clock_gettime(CLOCK_MONOTONIC, &end);
        total_time_spent += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

        print_function(buf, smc_recognizer.is_correct);

        clock_gettime(CLOCK_MONOTONIC, &start);
        SmcRecognizerContext_reset(&smc_recognizer._fsm);
        clock_gettime(CLOCK_MONOTONIC, &end);
        total_time_spent += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    }
    printf("Total time spent using smc: %.9lf seconds\n", total_time_spent);
    return 0;
}

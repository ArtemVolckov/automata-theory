#include <time.h>
#include <stdlib.h>
#include "config.h"

void gen_str(char* str, int max_add_len, int* position, const char* char_set, size_t char_set_len) { 
    if (max_add_len == 0) 
        return;
    int len = (rand() % max_add_len);
    
    for (int i = 0; i <= len; ++i) {
        str[*position] = char_set[rand() % char_set_len];
        *position += 1;
    }
}

void gen_char(char* str, int* position, const char* char_set, size_t char_set_len) {
    str[*position] = char_set[rand() % char_set_len];
    *position += 1;
}

void gen_strings(int strings, int max_command_length, int max_keylist_length) {

    // str_len = command len + space + keylist len + '\0' (max 256)

    int str_len = max_command_length + 1 + max_keylist_length + 1;
    char* str = (char*) calloc(str_len, 1);
    int position = 0;

    const char* command_char_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
    const char* blank_char_set   = "\t ";
    const char* keylist_char_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\t ";
    const char* allnum_char_set  = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    const size_t command_char_set_len = strlen(command_char_set);
    const size_t blank_char_set_len   = strlen(blank_char_set);
    const size_t keylist_char_set_len = strlen(keylist_char_set);
    const size_t allnum_char_set_len  = strlen(allnum_char_set);

    srand(time(0));

    for (int i = 0; i < strings; ++i) {
        gen_str (str, max_command_length, &position, command_char_set, command_char_set_len);   // Always
        gen_char(str, &position, blank_char_set, blank_char_set_len);                           // Always
        gen_str (str, max_keylist_length - 1, &position, keylist_char_set, keylist_char_set_len); // Optional
        gen_char(str, &position, allnum_char_set, allnum_char_set_len);                         // Always
        
        puts(str);
        memset(str, 0, str_len);
        position = 0;
    }
    free(str);
}

int main(int argc, const char* argv[]) {
    
    // Array of default parameters
    // params[0] -> number of strings
    // params[1] -> max command length
    // params[2] -> max keylitst length
    
    int params[3] = {1, 1, 1};

    char* end_ptr = NULL;

    if (argc > 4) {
        fprintf(stderr, "Usage: %s [number_of_strings] [max_command_length] [max_keylist_length]\n", *argv);
        fprintf(stderr, "       All parameters are optional.\n");
        return 1; 
    }
    for (int i = 1; i < argc; ++i) {
        params[i - 1] = strtol(argv[i], &end_ptr, 10);

        if (*end_ptr != '\0') {
            fprintf(stderr, "Error: Wrong format '%s'\n", argv[i]);
            return 1;
        }
        if (params[i - 1] < 1) {
            fprintf(stderr, "Error: '%s' must be greater than or equal to 1\n", argv[i]);
            return 1;
        }
    }
    if ((params[1] + params[2]) > (BUF_SIZE - 2)) {
        fprintf(stderr, "Error: The sum of parameters exceeds the maximum buffer size of %d\n", BUF_SIZE);
        return 1;
    }
    gen_strings(params[0], params[1], params[2]);
    return 0;
}

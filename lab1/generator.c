#include <time.h>
#include <stdlib.h>
#include "config.h"

void gen_command(char* str, int max_add_len, int* position, const char* char_set, size_t char_set_len) { 
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
    char buf[BUF_SIZE] = {0};
    int position = 0;
    int remaining;
    int current_key_len;

    const char* command_char_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
    const char* blank_char_set   = "\t ";
    const char* hyphen_char_set = "-"; 
    const char* allnum_char_set  = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    const size_t command_char_set_len = strlen(command_char_set);
    const size_t blank_char_set_len   = strlen(blank_char_set);
    const size_t allnum_char_set_len  = strlen(allnum_char_set);

    srand(time(0));

    for (int i = 0; i < strings; ++i) {
        remaining = max_keylist_length;
        gen_command(buf, max_command_length, &position, command_char_set, command_char_set_len); // Command
        
        while (remaining >= 3) {
            current_key_len = (rand() % remaining); 

            // single-character key 
            if (current_key_len == 2 || current_key_len == 3) {
                gen_char(buf, &position, blank_char_set, blank_char_set_len); // Blank
                gen_char(buf, &position, hyphen_char_set, 1);
                gen_char(buf, &position, allnum_char_set, allnum_char_set_len);
                remaining -= current_key_len + 1;
            }
            // multi-character key
            else if (current_key_len >= 4) {
                gen_char(buf, &position, blank_char_set, blank_char_set_len); // Blank
                gen_char(buf, &position, hyphen_char_set, 1);
                gen_char(buf, &position, hyphen_char_set, 1);

                for (int j = 2; j < current_key_len; ++j) 
                    gen_char(buf, &position, allnum_char_set, allnum_char_set_len);
                remaining -= current_key_len + 1;
            }
            else {
                continue;
            }
        }
        buf[position] = '\0';        
        puts(buf);
        position = 0;
    }
}

int main(int argc, const char* argv[]) {
    
    // Array of default parameters
    // params[0] -> number of strings
    // params[1] -> max command length
    // params[2] -> max keylitst length
    
    int params[3] = {1, 1, 3};

    char* end_ptr = NULL;

    if (argc > 4) {
        fprintf(stderr, "Usage: %s [number_of_strings] [max_command_length] [keylist_length]\n", *argv);
        fprintf(stderr, "       All parameters are optional.\n");
        return 1; 
    }
    for (int i = 1; i < argc; ++i) {
        params[i - 1] = strtol(argv[i], &end_ptr, 10);

        if (*end_ptr != '\0') {
            fprintf(stderr, "Error: Wrong format '%s'\n", argv[i]);
            return 1;
        }
        if (i == 3) {
            if (params[i - 1] < 2) {
                fprintf(stderr, "Error: '%s' must be greater than or equal to 3\n", argv[i]);
                return 1;
            }
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

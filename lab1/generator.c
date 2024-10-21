#include <stdlib.h>
#include <time.h>
#include "config.h"

/* CHAR SETS FOR GENERATING THINGS */
char *allnum_dot_slash = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
char *allnum           = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
char *blank            = "\t ";
char *hyphen           = "-"; 

void gen_command(char *str, int *pos, int max_len) {
  *pos = rand() % max_len;

  for (int i = 0; i <= *pos; ++i) 
    str[i] = allnum_dot_slash[rand() % 64];
  (*pos)++;  
}

void gen_allnum(char* str, int* pos) {
  str[*pos] = allnum[rand() % 62];
  (*pos) += 1;
}

void gen_blank(char* str, int* pos) {
  str[*pos] = blank[rand() % 2];
  (*pos) += 1;
}

void gen_hyphen(char* str, int* pos) {
  str[*pos] = hyphen[0];
  (*pos) += 1;
}

void gen_strings(int *params) {
  int key_len, remaining, pos;
  char buf[BUF_SIZE] = {0};
  srand(time(0));

  for (int i = 0; i < params[0]; ++i) {
    remaining = params[2];
    pos = 0;

    if (params[1] != 0) 
      gen_command(buf, &pos, params[1]);

    while (remaining >= 3) {
      key_len = (rand() % remaining);

      if (key_len < 2)
        continue;
      gen_blank(buf, &pos);
      gen_hyphen(buf, &pos);

      /* single-character key */
      if (key_len == 2 || key_len == 3) 
        gen_allnum(buf, &pos);

      /* multi-character key */
      else if (key_len >= 4) {
        gen_hyphen(buf, &pos);

        for (int j = 2; j < key_len; ++j) 
          gen_allnum(buf, &pos);
      }
      remaining -= (key_len + 1);
    }
    buf[pos] = '\0';        
    puts(buf);
  }
}

int main(int argc, const char* argv[]) {
  /* params[0] -> number of strings
   * params[1] -> max command length
   * params[2] -> max keylitst length */

  int params[3] = {1, 1, 3}; /* default values*/

  char *end_ptr = NULL;

  if (argc > 4) {
    fprintf(stderr, "Usage: %s [number_of_strings]           \
                     [max_command_length] [keylist_length]\n \
                     All parameters are optional.\n", *argv);
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
        fprintf(stderr, "Error: '%s' must be greater \
                         than or equal to 3\n", argv[i]);
        return 1;
      }
    }
    if (params[i - 1] < 1) {
      fprintf(stderr, "Error: '%s' must be greater \
                       than or equal to 1\n", argv[i]);
      return 1;
    }
  }
  if ((params[1] + params[2]) > (BUF_SIZE - 2)) {
    fprintf(stderr, "Error: The sum of parameters exceeds the \
                     maximum buffer size of %d\n", BUF_SIZE);
    return 1;
  }
  gen_strings(params);
  return 0;
}

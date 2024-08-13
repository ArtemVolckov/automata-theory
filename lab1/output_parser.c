#include "config.h"
#include "hashmap.h"

#define HASHMAP_CAPACITY 1
#define DELIM "\t \n"

void collect_statistics(Hashmap* h) {
    char buf[BUF_SIZE] = {0};
    char* token, *command;
    char* key_arr[BUF_SIZE];
    int counter = 0;

    while (fgets(buf, BUF_SIZE, stdin)) {
        token = strtok(buf, DELIM);
        command = token;

        while (token != NULL) {
            token = strtok(NULL, DELIM);
            if (token == NULL)
                continue;
            key_arr[counter] = token;
            counter++;
        }
        for (int i = 0; i < counter - 1; ++i) {
            for (int j = i + 1; j < counter; ++j) {
                if (strcmp(key_arr[i], key_arr[j]) == 0) {
                    for (int k = j; k < counter - 1; ++k) {
                        key_arr[k] = key_arr[k + 1];
                    }
                    counter -= 1;
                    j -= 1;
                } 
            }
        }
        hashmap_add(h, command, key_arr, counter);
        counter = 0;       
    }
}

int main() {
    Hashmap h;
    hashmap_init(&h, HASHMAP_CAPACITY, FACTOR);
    collect_statistics(&h);
    hashmap_print(&h);
    hashmap_free(&h);
    return 0;
}

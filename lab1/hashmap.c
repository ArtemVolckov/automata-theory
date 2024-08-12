#include "config.h"
#include "hashmap.h"

size_t get_hash(const char* str, size_t capacity) {
    size_t sum = 0;

    for(int i = 0; i < strlen(str); ++i)
        sum += str[i] * (i + 1);
    return (sum % capacity);
}

void hashmap_init(Hashmap* h, size_t capacity, double factor) {
    if (h == NULL || capacity < 1)
        abort();
    h->size = 0;
    h->capacity = capacity;
    h->factor = factor;
    h->items = (Item**) calloc(capacity, sizeof(Item*)); 
}

void hashmap_resize(Hashmap* h) {
    size_t old_capacity = h->capacity, size = h->size, size_save = h->size;
    size_t new_capacity = old_capacity * 2;
    Hashmap h_new;
    hashmap_init(&h_new, new_capacity, h->factor);

    size_t hash;
    Item* item_ptr, *new_item_ptr, *new_item_ptr_tmp;

    for (size_t i = 0; i < old_capacity && size != 0; ++i) {
        item_ptr = h->items[i];

        if (item_ptr != NULL) {
            size -= 1;
        }

        while (item_ptr != NULL) {
            hash = get_hash(item_ptr->command, new_capacity);
            new_item_ptr = h_new.items[hash];
            new_item_ptr_tmp = NULL;

            while (new_item_ptr != NULL) {
                new_item_ptr_tmp = new_item_ptr;
                new_item_ptr = new_item_ptr->next;
            }
            if (new_item_ptr_tmp == NULL) {
                h_new.items[hash] = item_ptr; 
            }
            else {
                new_item_ptr_tmp->next = item_ptr;
            }
            item_ptr = item_ptr->next; 
        } 
    }
    free(h->items);
    *h = h_new;
    h->size = size_save;
}

void hashmap_add(Hashmap* h, char* command, char* key_arr[], int key_arr_size) {
    if ((h->size / h->capacity) > h->factor) {
        hashmap_resize(h);
    }
    size_t hash = get_hash(command, h->capacity), command_len = strlen(command), key_len;
    Item* item_ptr = h->items[hash], *item_tmp = NULL;
    ListNode* list_ptr, *list_ptr_tmp;

    while (item_ptr != NULL) {
        if (strcmp(item_ptr->command, command) == 0) {
            int is_find = 0;

            for (int i = 0; i < key_arr_size; ++i) {
                list_ptr = item_ptr->keys;

                while (list_ptr != NULL) {
                    if (strcmp(list_ptr->key, key_arr[i]) == 0) {
                        is_find = 1;
                        break;
                    }
                    list_ptr_tmp = list_ptr;
                    list_ptr = list_ptr->next;      
                }
                if (is_find == 1) {
                    is_find = 0;
                    continue;
                }
                list_ptr_tmp->next = malloc(sizeof(ListNode));
                list_ptr_tmp = list_ptr_tmp->next;
                list_ptr_tmp->next = NULL;

                key_len = strlen(key_arr[i]);
                list_ptr_tmp->key = malloc(key_len + 1);
                strcpy(list_ptr_tmp->key, key_arr[i]);
                list_ptr_tmp->key[key_len] = '\0';
            }
            return;   
        }
        item_tmp = item_ptr;
        item_ptr = item_ptr->next;
    }
    if (item_tmp != NULL) {
        item_tmp->next = malloc(sizeof(Item));
        item_ptr = item_tmp->next;
    }
    else {
        h->items[hash] = malloc(sizeof(Item));
        item_ptr = h->items[hash];
        h->size += 1;
    }
    item_ptr->command = malloc(command_len+1);
    strcpy(item_ptr->command, command);
    item_ptr->command[command_len] = '\0';

    item_ptr->next = NULL;

    item_ptr->keys = malloc(sizeof(ListNode));
    list_ptr = item_ptr->keys;

    key_len = strlen(key_arr[0]);
    list_ptr->key = malloc(key_len + 1);
    strcpy(list_ptr->key, key_arr[0]);
    list_ptr->key[key_len] = '\0'; 
    
    for (int i = 1; i < key_arr_size; ++i) {
        list_ptr->next = malloc(sizeof(ListNode));
        list_ptr = list_ptr->next;

        key_len = strlen(key_arr[i]);
        list_ptr->key = malloc(key_len + 1);
        strcpy(list_ptr->key, key_arr[i]);
        list_ptr->key[key_len] = '\0'; 
    }
    list_ptr->next = NULL;
}

void hashmap_print(Hashmap* h) {
    if (h == NULL)
        return;
    Item* item_ptr = NULL; 
    ListNode* list_ptr = NULL;
    size_t size = h->size;
    size_t capacity = h->capacity;

    for (size_t i = 0; i < capacity && size != 0; ++i) {
        item_ptr = h->items[i];

        if (item_ptr != NULL) 
            size -= 1;

        while (item_ptr != NULL) {
            printf("Command: \"%s\" ", item_ptr->command);
            list_ptr = item_ptr->keys;
            printf("Keys:");

            while (list_ptr != NULL) {
                printf(" \"%s\"", list_ptr->key);
                list_ptr = list_ptr->next;
            }
            printf("\n");
            item_ptr = item_ptr->next; 
        } 
    }
}

void hashmap_free(Hashmap* h) {
    if (h == NULL)
        return;
    Item* item_ptr = NULL, *item_tmp = NULL;
    ListNode* list_ptr = NULL, *list_tmp = NULL;
    size_t size = h->size;
    size_t capacity = h->capacity;

    for (size_t i = 0; i < capacity && size != 0; ++i) {
        item_ptr = h->items[i];

        if (item_ptr != NULL)  
            size -= 1;

        while (item_ptr != NULL) {
            list_ptr = item_ptr->keys;

            while (list_ptr != NULL) {
                list_tmp = list_ptr->next;
                free(list_ptr->key);
                free(list_ptr);
                list_ptr = list_tmp;
            }
            item_tmp = item_ptr->next;
            free(item_ptr->command);
            free(item_ptr);
            item_ptr = item_tmp; 
        } 
    }
    free(h->items);
}

// Tests

#if 0
int main() {
    Hashmap h;
    hashmap_init(&h, 1, FACTOR);

    char command[] = "gcc";
    char* key_arr[] = { "-g", "-b" };
    int key_arr_size = sizeof(key_arr) / sizeof(key_arr[0]);
    hashmap_add(&h, command, key_arr, key_arr_size);

    char command2[] = "gc";
    char* key_arr2[] = { "bro", "my", "-b" };
    int key_arr_size2 = sizeof(key_arr2) / sizeof(key_arr2[0]);
    hashmap_add(&h, command2, key_arr2, key_arr_size2);

    char command3[] = "gcc";
    char* key_arr3[] = { "bro", "my", "-b" };
    int key_arr_size3 = sizeof(key_arr3) / sizeof(key_arr3[0]);
    hashmap_add(&h, command3, key_arr3, key_arr_size3);

    hashmap_print(&h);
    hashmap_free(&h);
}
#endif

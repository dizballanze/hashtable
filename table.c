/**
 * Hash table routines
 * implementation of table.h
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"

/* Initialize table. This function does't free items memory ! */
void hash_table_init(hash_table *table, uint64_t size) {
    table->items = (hash_table_item *) calloc(size, sizeof(hash_table_item));
    table->size = size;
    table->used_items_count = 0;
    hash_init_random(&table->hash_params);
}

/* Insert key value to the table */
uint64_t hash_table_insert(hash_table *table, char *key, char *value) {
    uint64_t curr_index;
    hash_table_item *curr_item;
    for (uint64_t iteration=0; iteration <= table->size; ++iteration) {
        curr_index = hash_string_iterable(&table->hash_params, table->size, iteration, key);
        curr_item = &table->items[curr_index];
        /* Insert on empty or deleted item */
        if (curr_item->is_deleted || !curr_item->is_init) {
            curr_item->is_deleted = 0;
            curr_item->is_init = 1;
            curr_item->key = key;
            curr_item->value = value;
            table->used_items_count++;
            return iteration;
        }
        /* Rewrite existed item */
        if (strcmp(curr_item->key, key) == 0) {
            curr_item->key = key;
            return iteration;
        }
    }
    return -1;
}

/* Search for key in hash table */
hash_table_item *hash_table_search(hash_table *table, char *key) {
    uint64_t curr_index;
    hash_table_item *curr_item;
    for (uint64_t iteration=0; iteration <= table->size; ++iteration) {
        curr_index = hash_string_iterable(&table->hash_params, table->size, iteration, key);
        curr_item = &table->items[curr_index];
        // Found
        if (curr_item->is_init && !curr_item->is_deleted && (strcmp(curr_item->key, key) == 0)) {
            return curr_item;
        }
        // Search completed
        if (!curr_item->is_init) {
            return NULL;
        }
    }
    return NULL;
}

/* Delete item by key */
uint8_t hash_table_delete_item_by_key(hash_table *table, char *key) {
    hash_table_item *found_item;
    found_item = hash_table_search(table, key);
    if (!found_item) {
        return 0;
    }
    found_item->is_deleted = 1;
    return 1;
}

/* Destroy table, clear memory */
void hash_table_destroy(hash_table *table, uint8_t clear_keys) {
    hash_table_item *curr_item;
    if (clear_keys) {
        for (uint64_t i; i < table->size; i++) {
            curr_item = &table->items[i];
            if (curr_item->is_init) {
                free(curr_item->key);
                free(curr_item->value);
            }
        }
    }
    free(table->items);
    table->size = 0;
    table->used_items_count = 0;
}

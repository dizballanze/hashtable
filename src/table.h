#ifndef _TABLE_H
#define _TABLE_H

/**
 * Hash table interface
 */

#include "hash.h"


typedef struct hash_table_item hash_table_item;
struct hash_table_item {
    char *key;
    char *value;
    uint8_t is_deleted;
    uint8_t is_init;
};

typedef struct hash_table hash_table;
struct hash_table {
    uint64_t size;
    uint64_t used_items_count;
    uint64_t not_deleted_used_items_count;
    hash_function_params hash_params;
    hash_table_item *items;
};


void hash_table_init(hash_table *table, uint64_t size);
uint64_t hash_table_insert(hash_table *table, char *key, char *value);
hash_table_item *hash_table_search(hash_table *table, char *key);
uint8_t hash_table_delete_item_by_key(hash_table *table, char *key);
void hash_table_destroy(hash_table *table, uint8_t clear_keys);
uint8_t hash_table_extend(hash_table *table, uint64_t new_size);

#endif

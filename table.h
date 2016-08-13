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
    hash_function_params hash_params;
    hash_table_item *items;
};


void hash_table_init(hash_table *table, uint64_t size);

uint64_t hash_table_insert(hash_table *table, char *key, char *value);

hash_table_item *hash_table_search(hash_table *table, char *key);

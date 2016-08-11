/**
 * Hash table interface
 */

typedef struct hash_table_item hash_table_item;
struct hash_table_item {
    uint64_t key;
    char *value;
    uint8_t is_deleted;
    uint8_t is_init;
};

typedef struct hash_table hash_table;
struct hash_table {
    uint64_t size;
    hash_table_item *items;
};

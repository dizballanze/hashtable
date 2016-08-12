/**
 * Hash table routines
 * implementation of table.h
 */

#include <stdint.h>
#include <stdlib.h>

#include "table.h"

/* Initialize table. This function does't free items memory ! */
void hash_table_init(hash_table *table, uint64_t size) {
    table->items = (hash_table_item *) calloc(size, sizeof(hash_table_item));
    table->size = size;
    table->used_items_count = 0;
    hash_init_random(&table->hash_params);
}

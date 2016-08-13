#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "table.h"


int main(void) {
    char key[] = "sample-key";
    char key2[] = "sample-key2";
    char value[] = "Item 1";
    char value2[] = "Item 2";
    hash_table_item *found_item;
    hash_table table;
    hash_table_init(&table, 128);
    printf("prime: %" PRIu64 "\n", table.hash_params.prime);
    hash_table_extend(&table, 256);
    printf("prime: %" PRIu64 "\n", table.hash_params.prime);
    hash_table_insert(&table, key, value);
    hash_table_insert(&table, key2, value2);
    found_item = hash_table_search(&table, key);
    printf("%s\n", found_item->value);
    found_item = hash_table_search(&table, key2);
    printf("%s\n", found_item->value);
    hash_table_delete_item_by_key(&table, key);
    found_item = hash_table_search(&table, key);
    if (found_item) {
        printf("Found\n");
    } else {
        printf("Not found\n");
    }
    hash_table_destroy(&table, 1);
    return 0;
}

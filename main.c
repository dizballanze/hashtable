#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "table.h"


int main(void) {
    char key[] = "sample-key";
    char key2[] = "sample-key2";
    char value[] = "Hello world!";
    hash_table table;
    hash_table_init(&table, 10000);
    printf("prime: %" PRIu64 "\n", table.hash_params.prime);
    printf("used items: %" PRIu64 "\n", table.used_items_count);
    hash_table_insert(&table, key, value);
    printf("used items: %" PRIu64 "\n", table.used_items_count);
    hash_table_insert(&table, key, value);
    printf("used items: %" PRIu64 "\n", table.used_items_count);
    hash_table_insert(&table, key2, value);
    printf("used items: %" PRIu64 "\n", table.used_items_count);
    return 0;
}

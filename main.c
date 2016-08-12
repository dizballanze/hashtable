#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "table.h"


int main(void) {
    char str[] = "Hello world";
    uint64_t values[128];
    for (size_t i=0; i < 128; i++)
        values[i] = 0;
    hash_table table;
    hash_table_init(&table, 10000);
    printf("prime: %" PRIu64 "\n", table.hash_params.prime);
    uint64_t curr_value;
    for (size_t i=0; i < 128; i++) {
        curr_value = hash_string_iterable(&table.hash_params, 128, i, (char *) &str);
        if (values[curr_value])
            printf("Duplicate: %" PRIu64 "\n", curr_value);
        values[curr_value] = 1;
        printf("%" PRIu64 ": %" PRIu64 "\n", i, curr_value);
    }
    return 0;
}

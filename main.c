#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "table.h"


int main(void) {
    /*hash_function_params instance;*/
    /*hash_create_random(&instance);*/
    /*printf("Prime: %" PRIu64 "\n", instance.prime);*/
    /*printf("a: %" PRIu64 "\n", instance.hash_coef_a);*/
    /*printf("b: %" PRIu64 "\n", instance.hash_coef_b);*/
    /*char str[] = "Hello world";*/
    /*printf("hashed: %" PRIu64 "\n", hash_string(&instance, 1000, (char *)&str));*/
    /*printf("hashed: %" PRIu64 "\n", hash_string(&instance, 1000, (char *)&str));*/
    hash_table table;
    hash_table_init(&table, 10000);
    printf("prime: %" PRIu64 "\n", table.hash_params->prime);

    return 0;
}

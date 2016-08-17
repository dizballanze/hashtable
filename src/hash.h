#ifndef _HASH_H
#define _HASH_H

/**
 * Universal hashing interface
 */

#include <stdint.h>


typedef struct hash_function_params hash_function_params;
struct hash_function_params {
    uint64_t prime;
    uint64_t hash_coef_a;
    uint64_t hash_coef_b;
};


uint64_t hash_string_iterable(
        hash_function_params *instance, uint64_t table_size, uint64_t iteration, char *key);

void hash_init_random(hash_function_params *instance);

#endif

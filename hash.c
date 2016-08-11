/**
 * Universal hashing routines
 * implementation of hash.h
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash.h"
#include "prime.h"


/* Hash int key */
uint64_t hash_int(hash_function_params *instance, uint64_t table_size, uint64_t key) {
    return (((instance->hash_coef_a * key) + instance->hash_coef_b) % instance->prime) % table_size;
}

/* Hash string key */
uint64_t hash_string(hash_function_params *instance, uint64_t table_size, char *key) {
    size_t key_length = strlen(key);
    uint64_t key_sum = 0;
    for (size_t i = 0; i < key_length; i++) {
        key_sum = (uint8_t) key[i] * pow((double)instance->hash_coef_a, (double)i);
    }
    return hash_int(instance, table_size, key_sum);
}

/* Create new hash instance */
void hash_init_random(hash_function_params *instance) {
    instance->prime = prime_random_generate();
    instance->hash_coef_a = rand() % instance->prime;
    instance->hash_coef_b = rand() % instance->prime;
}

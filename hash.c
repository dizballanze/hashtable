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
uint64_t hash_int(hash_function_params *instance, uint64_t key) {
    return ((instance->hash_coef_a * key) + instance->hash_coef_b) % instance->prime;
}

/* Hash string key */
uint64_t hash_string(hash_function_params *instance, char *key) {
    size_t key_length = strlen(key);
    uint64_t key_sum = 0;
    for (size_t i = 0; i < key_length; i++) {
        key_sum = (uint8_t) key[i] * pow((double)instance->hash_coef_a, (double)i);
    }
    return key_sum;
}

/**
 * Iterable hashing for open indexation:
 * h(k) = (h1(h) + i * h2(k)) mod m
 */
uint64_t hash_string_iterable(hash_function_params *instance, uint64_t table_size, uint64_t iteration, char *key) {
    uint64_t h_value, h2_value;
    h_value = hash_int(instance, hash_string(instance, key));
    if (iteration) {
        h2_value = h_value;
        // Should be odd
        if ((h2_value % 2) == 0) {
           h2_value += 1;
        }
        h_value = h_value + iteration * h2_value;
    }
    return h_value % table_size;
}

/* Create new random hash instance */
void hash_init_random(hash_function_params *instance) {
    instance->prime = prime_random_generate();
    instance->hash_coef_a = rand() % instance->prime;
    instance->hash_coef_b = rand() % instance->prime;
}

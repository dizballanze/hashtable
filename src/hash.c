/**
 * Universal hashing routines
 * implementation of hash.h
 */

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
    // Horner's rule
    uint64_t key_sum = 0;
    uint64_t coef = 1;
    for (size_t i = 0; i < key_length; i++) {
        key_sum += key[i] * coef;
        coef *= instance->hash_coef_a;
    }
    return key_sum;
}

/**
 * Iterable hashing for open indexation:
 * h(k) = (h1(h) + i * h2(k)) mod m
 */
uint64_t hash_string_iterable(hash_function_params *instance, uint64_t table_size, uint64_t iteration, char *key) {
    uint64_t h_value;
    h_value = hash_int(instance, hash_string(instance, key));
    h_value = h_value + iteration * (h_value * 2 + 1);
    return h_value % table_size;
}

/* Create new random hash instance */
void hash_init_random(hash_function_params *instance) {
    instance->prime = prime_random_generate();
    instance->hash_coef_a = rand() % instance->prime;
    instance->hash_coef_b = rand() % instance->prime;
}

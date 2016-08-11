/**
 * Universal hashing routines
 * implementation of hash.h
 */

#include <stdint.h>

#include "hash.h"
#include "prime.h"


/* Hash int key */
uint64_t hash_int(hash_instance *instance, uint64_t table_size, uint64_t key) {
    return (((instance->hash_coef_a * key) + instance->hash_coef_b) % instance->prime) % table_size;
}

/* Create new hash instance */
void hash_create_random(hash_instance *instance) {
    instance->prime = prime_random_generate();
}

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "prime.h"
#include "hash.h"


int main(void) {
    /*uint64_t number = prime_random_generate();*/
    /*printf("%" PRIu64 "\n", number);*/
    hash_instance instance;
    hash_create_random(&instance);
    printf("%" PRIu64 "\n", instance.prime);
    return 0;
}

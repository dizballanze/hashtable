#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "prime.h"


int main(void) {
    uint64_t number = prime_random_generate();
    printf("%" PRIu64 "\n", number);
    return 0;
}

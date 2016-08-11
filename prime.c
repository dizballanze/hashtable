/*
 * Prime numbers generation routines.
 * implemetation of prime.h
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "prime.h"


/* Calculate a ^ b (mod n) */
uint64_t prime_modular_exponentiation(uint64_t a, uint64_t b, uint64_t n) {
    uint64_t res = 1;
    while (b) {
        a = (a * a) % n;
        if (b & 1ULL) {
            res = (res * a) % n;
        }
        b = (b >> 1ULL);
    }
    return res;
}

/* Trial division test */
uint8_t prime_trial_division_test(uint64_t number) {
    uint64_t number_sqrt;
    number_sqrt = (uint64_t) sqrtl((long double) number);
    for (uint64_t i=1, j=6*i-1; j<=number_sqrt; ++i, j=6*i-1) {
        if (((number % j) == 0) || ((number % (j + 2)) == 0)) {
            return 0;
        }
    }
    return 1;
}

/* Test if number is prime */
uint8_t prime_test(uint64_t number) {
    return (prime_modular_exponentiation(2, number - 1, number) == 1) && prime_trial_division_test(number);
}

/* Return random 32bit prime integer  */
uint64_t prime_random_generate(void) {
    uint64_t number;
    srand(time(0));
    number = rand();
    while (!prime_test(number)) {
        number--;
    };
    return number;
}

/*
int main(void) {
    uint64_t number;
    number = prime_random_generate();
    printf("%llu\n", number);
    return 0;
}*/

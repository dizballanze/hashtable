/**
 * Universal hashing interface
 */


typedef struct hash_function_params hash_function_params;
struct hash_function_params {
    uint64_t prime;
    uint64_t hash_coef_a;
    uint64_t hash_coef_b;
};


void hash_init_random(hash_function_params *instance);
uint64_t hash_int(hash_function_params *instance, uint64_t table_size, uint64_t key);
uint64_t hash_string(hash_function_params *instance, uint64_t table_size, char *key);

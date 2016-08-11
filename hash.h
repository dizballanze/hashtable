/**
 * Universal hashing interface
 */


struct hash_instance {
    uint64_t prime;
    uint64_t hash_coef_a;
    uint64_t hash_coef_b;
};

typedef struct hash_instance hash_instance;

uint64_t hash_int(hash_instance *instance, uint64_t table_size, uint64_t key);
void hash_create_random(hash_instance *instance);

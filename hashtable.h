#define TABLE_SIZE 1000

typedef struct {
    char *key;
    int value;
} hash_pair;

typedef struct {
    hash_table *pairs;
    int num_pair; 
} hash_bucket;

typedef struct {
    hash_bucket *buckets;
    int num_bucket;
} hash_table;


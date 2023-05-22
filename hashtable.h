#define TABLE_SIZE 1000

typedef struct hp {
    char *key;
    int value;
} hash_pair;

typedef struct hb {
    hash_pair *pairs;
    int num_pairs; 
} hash_bucket;

typedef struct ht {
    hash_bucket *buckets;
    int num_bucket;
} hash_table;

size_t hashFunction(char *key);

hash_pair *createPair(char *key, int value);
hash_table *createTable();
void deleteTable();

hash_table *insertKey(hash_table *table, char *key, int value);
hash_pair *searchKey(hash_table *table, char *key);
hash_table *removeKey(hash_table *table, char *key);

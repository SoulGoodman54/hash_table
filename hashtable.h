#include <stddef.h>
#define TABLE_SIZE 50


#ifndef MY_HEADER
#define MY_HEADER
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
#endif

size_t hashFunction(char *key);

hash_pair *createPair(char *key, int value);
hash_table *createTable();
void deleteTable();

hash_table *addBucket(hash_table *table, hash_bucket *bucket, size_t index, int size_bucket);

hash_table *insertKey(hash_table *table, char *key, int value);
hash_pair  *searchKey(hash_table *table, char *key);
hash_table *removeKey(hash_table *table, char *key);

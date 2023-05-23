#include <stddef.h>
#include <stdbool.h>

#define check {printf ("%s : %d\n", __FILE__, __LINE__);}

#define TABLE_SIZE 10
#define BUCKET(i) (table->buckets[i])


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
    int num_buckets;
    int num_elems;
    bool *bloom_filter;
} hash_table;
#endif

size_t hashFunction(char *key, int size);

hash_pair *createPair(char *key, int value);
hash_table *createTable();
hash_table *rehash(hash_table *table);
void deleteTable();

hash_table *addBucket(hash_table *table, hash_bucket *bucket, size_t index, int size_bucket);

hash_table *insertKey(hash_table *table, char *key, int value);
hash_pair  *searchKey(hash_table *table, char *key);
hash_table *removeKey(hash_table *table, char *key);

hash_table *addToFilter(hash_table *table, char *key);
bool testByFilter(hash_table *table, char *key);

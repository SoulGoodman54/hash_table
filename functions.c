#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "hashtable.h"

size_t hashFunction(char *key){

    int a = 1, q = 3889;
    size_t ret = 0;

    for (int i = 0; i <= strlen(key); i++){

        ret += (a * key[i]) % TABLE_SIZE;
        a = (a * q) % TABLE_SIZE;   
    }

    return ret;
}

hash_pair *createPair (char *key, int value){

    hash_pair *pair = (hash_pair*) malloc(sizeof(hash_pair));
    pair->key = strdup(key);
    pair->value = value;

    return pair;
}

hash_table *createTable(){
    
    hash_table *table = (hash_table *) malloc(sizeof(hash_table));  
    table->buckets = (hash_bucket*) calloc(TABLE_SIZE, sizeof(hash_bucket));
    table->num_bucket = TABLE_SIZE;
    
    for (int i = 0; i < TABLE_SIZE; i++){
        
        table->buckets[i].pairs = NULL;
        table->buckets[i].num_pairs = 0;
    }

    return table;
}

void deleteTable(hash_table *table){

    for (int i = 0; i < TABLE_SIZE; i++){

        if(table->buckets[i].pairs != NULL){

            free(table->buckets[i].pairs->key);
            free(table->buckets[i].pairs);
        }
    }

    free(table->buckets);
    free(table);
}

hash_table *insertKey(hash_table *table, char *key, int value){

    size_t index = hashFunction(key);
    hash_bucket *bucket = &table->buckets[index];

    bucket->num_pairs++;
    bucket->pairs = (hash_pair*) realloc(bucket->pairs, bucket->num_pairs * sizeof(hash_pair));

    hash_pair *pair = createPair(key, value);
    bucket->pairs[bucket->num_pairs-1] = *pair; 

    return table;
}

hash_pair *searchKey(hash_table *table, char *key){

    size_t index = hashFunction(key);

    if (table->buckets + index == NULL) 
        return NULL;

    hash_bucket *bucket = &table->buckets[index]; 

    for (int i = 0; i < bucket->num_pairs; i++){

        if (strcmp(bucket->pairs[i].key, key) == 0)
            return &bucket->pairs[i];
    }

    return NULL;
}

#define LASTPAIR bucket->pairs[bucket->num_pairs]

hash_table *removeKey(hash_table *table, char *key){

    size_t index = hashFunction(key);
    if (table->buckets + index == NULL)
        return table;

    hash_bucket *bucket = &table->buckets[index];

    for (int i = 0; i < bucket->num_pairs; i++){

        if (strcmp(bucket->pairs[i].key, key) == 0){

            if (i + 1 >= bucket->num_pairs){
                
                free(LASTPAIR.key);
                free(&LASTPAIR);

                bucket->num_pairs--;
                bucket->pairs = (hash_pair*) realloc(bucket->pairs, bucket->num_pairs * sizeof(hash_pair));

                return table;
            }             

            for (int j = 0; j < bucket->num_pairs; j++){

                if      (j < i) bucket->pairs[j] = bucket->pairs[i];
                else if (j > i) bucket->pairs[j] = bucket->pairs[i-1];

                free(LASTPAIR.key);
                free(&LASTPAIR); 

                bucket->num_pairs--;
                bucket->pairs = (hash_pair*) realloc(bucket->pairs, bucket->num_pairs * sizeof(hash_pair));
            }
        }
    }

    return table;
}
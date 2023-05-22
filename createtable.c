#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

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
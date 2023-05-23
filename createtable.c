#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t hashFunction(char *key, int table_size){

    int a = 1, q = 37;
    size_t ret = 0;

    for (int i = 0; i <= strlen(key); i++){

        ret = (ret + (a * key[i])) % table_size;
        a = (a * q) % table_size;   
    }

    return ret;
}

hash_pair *createPair (char *key, int value){

    hash_pair *pair = (hash_pair*) malloc(sizeof(hash_pair));
    pair->key = strdup(key);
    pair->value = value;

    return pair;
}

hash_table *createTable(int size){
    
    hash_table *table = (hash_table *) malloc(sizeof(hash_table));  
    table->buckets = (hash_bucket*) calloc(size, sizeof(hash_bucket));
    table->bloom_filter = (bool*) calloc(size, sizeof(bool));

    table->num_buckets = size;
    table->num_elems = 0;

    memset(table->bloom_filter, false, size);
    
    for (int i = 0; i < size; i++){
        
        table->buckets[i].pairs = NULL;
        table->buckets[i].num_pairs = 0;
    }

    return table;
}

void deleteTable(hash_table *table){

    for (int i = 0; i < table->num_buckets; i++){

        if(table->buckets[i].pairs != NULL){

            free(table->buckets[i].pairs->key);
            free(table->buckets[i].pairs);
        }
    }

    free(table->buckets);
    free(table->bloom_filter);
    free(table);
}

hash_table *rehash(hash_table *table){

    hash_table *new_table = createTable (table->num_buckets * 2);
    new_table->num_elems = table->num_elems;
    
    table->buckets = (hash_bucket*) realloc(table->buckets, table->num_buckets * sizeof(hash_bucket));

    for (int index = 0; index < table->num_buckets; index++){
    
        for (int i = 0; i < BUCKET(index).num_pairs; i++){
            
            new_table = insertKey(new_table, BUCKET(index).pairs[i].key, BUCKET(index).pairs[i].value);
        }
    }

    deleteTable(table);
    return new_table;
}
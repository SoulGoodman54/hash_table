#include <string.h>
#include <stdlib.h>
#include "hashtable.h"

hash_table *create_table(){
    
    hash_table *table = (hash_table *) malloc(sizeof(hash_table));  
    table->buckets = (hash_bucket*) calloc(TABLE_SIZE, sizeof(hash_bucket));
    table->num_bucket = TABLE_SIZE;
    
    for (int i = 0; i < TABLE_SIZE; i++){
        
        table->buckets[i].pairs = NULL;
        table->buckets[i].num_pair = 0;
    }

    return table;
}

void delete_table(hash_table *table){

    for (int i = 0; i < TABLE_SIZE; i++){

        if(table->buckets[i].pairs != NULL){

            free(table->buckets[i].pairs->key);
            free(table->buckets[i].pairs);
        }
    }

    free(table->buckets);
    free(table);
}
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hashtable.h"


hash_pair *searchKey(hash_table *table, char *key){

    if (!testByFilter(table, key))
        return NULL;
    
    size_t index = hashFunction(key, table->num_buckets);

    for (int i = 0; i < BUCKET(index).num_pairs; i++){

        if (strcmp(BUCKET(index).pairs[i].key, key) == 0)
            return &BUCKET(index).pairs[i];
    }

    return NULL;
}

hash_table *insertKey(hash_table *table, char *key, int value){

    if(searchKey(table, key)) return table;
    
    table = addToFilter(table, key);

    size_t index = hashFunction(key, table->num_buckets);

    if (BUCKET(index).num_pairs == 0){

        BUCKET(index).pairs = createPair(key, value);
        BUCKET(index).num_pairs++;
        table->num_elems++;
        return table;
    }

    table->num_elems++;
    BUCKET(index).num_pairs++;
    BUCKET(index).pairs = (hash_pair*) realloc(BUCKET(index).pairs, BUCKET(index).num_pairs * sizeof(hash_pair));

    BUCKET(index).pairs[BUCKET(index).num_pairs-1].key = strdup(key);
    BUCKET(index).pairs[BUCKET(index).num_pairs-1].value = value;

    if (table->num_elems > table->num_buckets * 5 / 3)
        table = rehash(table);

    return table;
}

void copyPair(hash_pair *a, hash_pair *b){

    a->key = strdup(b->key);
    a->value = b->value;
}

#define LASTPAIR BUCKET(index).pairs[BUCKET(i).num_pairs-1]

hash_table *removeKey(hash_table *table, char *key){

    if (!testByFilter(table, key))
        return table;    
    
    size_t index = hashFunction(key, table->num_buckets); 

    for (int i = 0; i < BUCKET(index).num_pairs; i++){

        if (strcmp(BUCKET(index).pairs[i].key, key) == 0){            

            for (int j = 0; j < BUCKET(index).num_pairs; j++)
                if (j > i) copyPair (BUCKET(index).pairs + j - 1, BUCKET(index).pairs + j);

            free(LASTPAIR.key);

            table->num_elems--;
            BUCKET(index).num_pairs--;
            BUCKET(index).pairs = (hash_pair*) realloc(BUCKET(index).pairs, BUCKET(index).num_pairs * sizeof(hash_pair));

            return table;
        }
    }

    return table;
}
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hashtable.h"


hash_table *insertKey(hash_table *table, char *key, int value){

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

    hash_pair *pair = createPair(key, value);
    BUCKET(index).pairs[BUCKET(index).num_pairs-1] = *pair;
    free(pair); 

    return table;
}

hash_pair *searchKey(hash_table *table, char *key){

    size_t index = hashFunction(key, table->num_buckets);

    if (&table->buckets[index] == NULL) 
        return NULL;
 

    for (int i = 0; i < BUCKET(i).num_pairs; i++){

        if (strcmp(BUCKET(index).pairs[index].key, key) == 0)
            return &BUCKET(index).pairs[i];
    }

    return NULL;
}

void eqPair(hash_pair *a, hash_pair *b){

    a->key = strdup(b->key);
    a->value = b->value;
}

#define LASTPAIR BUCKET(index).pairs[BUCKET(i).num_pairs-1]

hash_table *removeKey(hash_table *table, char *key){

    size_t index = hashFunction(key, table->num_buckets);
    if (BUCKET(index).num_pairs == 0)
        return table;

    for (int i = 0; i < BUCKET(index).num_pairs; i++){

        if (strcmp(BUCKET(index).pairs[i].key, key) == 0){            

            for (int j = 0; j < BUCKET(index).num_pairs; j++)
                if (j > i) eqPair (BUCKET(index).pairs + j - 1, BUCKET(index).pairs + j);

            free(LASTPAIR.key);

            table->num_elems--;
            BUCKET(index).num_pairs--;
            BUCKET(index).pairs = (hash_pair*) realloc(BUCKET(index).pairs, BUCKET(index).num_pairs * sizeof(hash_pair));

            return table;
        }
    }

    return table;
}
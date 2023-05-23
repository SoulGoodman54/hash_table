#include <stdlib.h>
#include "hashtable.h"

hash_table *addToFilter (hash_table *table, char *key){

    table->bloom_filter[hashFunction(key, table->num_buckets)] = true;
    return table;
}

bool testByFilter (hash_table *table, char *key){

    if (table->bloom_filter[hashFunction(key, table->num_buckets)]) 
        return true;
    
    return false;
}
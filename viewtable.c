#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>


void printBucket(hash_table *table, size_t index, FILE *file){

    hash_bucket *bucket = &table->buckets[index];
    fprintf(file, "%ld ", index + 1);

    if (bucket->num_pairs == 0){

        fprintf(file, "-\n");
        return;
    }

    for (int i = 0; i < bucket->num_pairs; i++){

        fprintf(file, "{%s, %d} -> ", bucket->pairs[i].key, bucket->pairs[i].value);
    }

    fprintf(file, "endl;\n");
}

void printTable(hash_table *table, FILE* file){

    for (size_t index = 0; index < table->num_buckets; index++)
        printBucket(table, index, file);
}

void printBloomFilter(hash_table *table, FILE *file){

    for (int i = 0; i < table->num_buckets; i++)
        fprintf(file, "| %d ", table->bloom_filter[i]);
    
    fprintf(file, "|\n");
}



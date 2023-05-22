#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>


void printBucket(hash_table *table, size_t index, FILE *file){

    hash_bucket *bucket = &table->buckets[index];

    if (bucket->num_pairs == 0){

        fprintf(file, "-");
        return;
    }

    for (int i = 0; i < bucket->num_pairs; i++){

        fprintf(file, "{%s, %d} -> ", bucket->pairs[i].key, bucket->pairs[i].value);
    }

    fprintf(file, "end of the bucket;\n");
}

void printTable(hash_table *table, FILE* file){

    for (size_t index = 0; index < TABLE_SIZE; index++)
        printBucket(table, index, file);
}

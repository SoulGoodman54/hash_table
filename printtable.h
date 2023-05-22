#include <stdio.h>
#include <stddef.h>
#include "hashtable.h"

void printBucket (hash_table *table, size_t index, FILE *file);
void printTable  (hash_table *table, FILE *file);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "printtable.h"


int main(){

    hash_table *table = createTable(TABLE_SIZE);
    
    table = insertKey(table, "asda", 5); 

    FILE *table1 = fopen("table1", "w");
    printTable(table, table1);
    printBloomFilter (table, stdout);
    fclose(table1);

    table = rehash(table);

    FILE *table2 = fopen("table2", "w");
    printTable(table, table2);
    printBloomFilter (table, stdout);
    fclose(table2);

    deleteTable(table);

    return 0;
}
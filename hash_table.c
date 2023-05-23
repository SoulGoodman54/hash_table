#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "printtable.h"


int main(){

    hash_table *table = createTable(TABLE_SIZE);
    table = insertKey(table, "asda", 5); 

    printTable(table, stdout);
    deleteTable(table);

    return 0;
}
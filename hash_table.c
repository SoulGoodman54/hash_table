#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "printtable.h"


int main(){

    hash_table *table = createTable();

    table = insertKey(table, "H", 2);
    table = insertKey(table, "H", 228); 
    table = removeKey(table, "H");
    
    printTable(table, stdout);


    deleteTable(table);
    return 0;
}
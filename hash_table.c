#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "printtable.h"


int main(){

    hash_table *table = createTable(TABLE_SIZE);
    int word_size = 0, let = 0;

    FILE *keys = fopen("keys", "w");
    for (int word = 0; word < 100000; word++){

        word_size = rand() % 10 + 1;
        for (int letter = 0; letter < word_size; letter++){

            let = rand() % 90 + 33;
            fprintf(keys, "%c", let);
        } 
        fprintf(keys, "\n");
    }
    fclose(keys);

    char key[10];
    FILE *ins = fopen("keys", "r");
    for (int i = 0; fscanf(ins, "%s", key) == 1; i++){
        table = insertKey(table, key, i + 1);
    }

    FILE *table1 = fopen("table1", "w");
    printTable(table, table1);
    fclose(table1);

    deleteTable(table);

    return 0;
}
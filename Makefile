CC = gcc
OBJECT += hash_table.o functions.o viewtable.o createtable.o bloomfilter.o

all: ht 

ht: $(OBJECT)
	$(CC) $(OBJECT) -o ht

*.o: *.c
	$(CC) *.c -c

clean: 
	rm -rf *.o ht
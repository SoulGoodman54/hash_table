CC = gcc
OBJECT += hash_table.o functions.o 

all: ht 

ht: $(OBJECT)
	$(CC) $(OBJECT) -o ht

*.o: *.c
	$(CC) *.c -c

clean: 
	rm -rf *.o ht
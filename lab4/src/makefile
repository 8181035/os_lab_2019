CC=gcc
CFLAGS=-I.

parallel_min_max : utils.o find_min_max1.o utils.h find_min_max1.h
    $(CC) -o parallel_min_max utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

process_memory : process_memory.o
    $(CC) -o process_memory  process_memory.c $(CFLAGS)

utils.o : utils.h
    $(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max1.o : utils.h find_min_max1.h
    $(CC) -o find_min_max1.o -c find_min_max.c $(CFLAGS)

process_memory.o : process_memory.c
    $(CC) -o process_memory.o -c process_memory.c $(CFLAGS)

clean :
    rm utils.o find_min_max.o process_memory.o  parallel_min_max process_memory 
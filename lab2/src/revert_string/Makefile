# Makefile for Revert_string project
bin: main.o librevert.a
	gcc -o bin main.o -L. -lrevert
    
main.o: main.c
	gcc -c main.c

librevert.a: revert_string.o
	ar cr librevert.a revert_string.o

revert_string.o: revert_string.c
	gcc -c revert_string.c


clean:
	rm -f *.o *.a bin
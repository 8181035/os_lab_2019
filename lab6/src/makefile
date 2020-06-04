CC=gcc
CFLAGS=-I.

client : client.o 
	$(CC) -o client client.o client.c $(CFLAGS)

server : server.o 
	$(CC) -o server server.o server.c $(CFLAGS)

client.o : client.c
	 $(CC) -o client.o -c client.c $(CFLAGS)

server.o : server.c
	 $(CC) -o server.o -c server.c $(CFLAGS)

clean :
    rm client.o server.o 
CC=gcc
CFLAGS=-c -m64
LFLAGS=-m64 -lnsl -lsocket -lresolv

all: tlserv tlclient

tlserv: server.o
	$(CC) $(LFLAGS) server.o -o server

server.o: server.c
	$(CC) $(CFLAGS) server.c
	
tlclient: client.o
	$(CC) $(LFLAGS) client.o -o client

client.o: client.c
	$(CC) $(CFLAGS) client.c
	
clean:
	rm -rf *.o bcmp

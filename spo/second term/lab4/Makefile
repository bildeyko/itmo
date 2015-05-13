CC=gcc
CFLAGS=-c -m64
LFLAGS=-m64

all: bcmp

bcmp: main.o io.o
	$(CC) $(LFLAGS) main.o io.o -o bcmp

main.o: main.c
	$(CC) $(CFLAGS) main.c
	
io.o: io.c
	$(CC) $(CFLAGS) io.c
	
clean:
	rm -rf *.o bcmp

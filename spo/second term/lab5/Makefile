CC=gcc
CFLAGS=-c -m64
LFLAGS=-m64
PTH_LFLAGS=-lpthread -lrt

all: 1_1 1_2 2_4 2_5 3_9 3_10

1_1:1_1_server 1_1_client

1_1_server: 1_1_server.o
	$(CC) $(LFLAGS) 1_1_server.o -o 1_1_server

1_1_server.o: 1_1_server.c
	$(CC) $(CFLAGS) 1_1_server.c
	
1_1_client: 1_1_client.o
	$(CC) $(LFLAGS) 1_1_client.o -o 1_1_client

1_1_client.o: 1_1_client.c
	$(CC) $(CFLAGS) 1_1_client.c

1_2:1_2_server 1_2_client

1_2_server: 1_2_server.o
	$(CC) $(LFLAGS) 1_2_server.o -o 1_2_server

1_2_server.o: 1_2_server.c
	$(CC) $(CFLAGS) 1_2_server.c
	
1_2_client: 1_2_client.o
	$(CC) $(LFLAGS) 1_2_client.o -o 1_2_client

1_2_client.o: 1_2_client.c
	$(CC) $(CFLAGS) 1_2_client.c
	
2_4: 2_4.o
	$(CC) $(LFLAGS) $(PTH_LFLAGS) 2_4.o -o 2_4

2_4.o: 2_4.c
	$(CC) $(CFLAGS) 2_4.c
	
2_5: 2_5.o
	$(CC) $(LFLAGS) $(PTH_LFLAGS) 2_5.o -o 2_5

2_5.o: 2_5.c
	$(CC) $(CFLAGS) 2_5.c
	
3_9: 3_9.o
	$(CC) $(LFLAGS) 3_9.o -o 3_9

3_9.o: 3_9.c
	$(CC) $(CFLAGS) 3_9.c
	
3_10: 3_10.o
	$(CC) $(LFLAGS) 3_10.o -o 3_10

3_10.o: 3_10.c
	$(CC) $(CFLAGS) 3_10.c
	
clean:
	rm -rf *.o bcmp

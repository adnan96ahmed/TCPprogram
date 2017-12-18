CC = gcc
CFLAGS = -Wall -g

all: client server runScript

client: TCPclient.c
	$(CC) $(CFLAGS) -o client TCPclient.c
	
server: TCPserver.c
	$(CC) $(CFLAGS) -o server TCPserver.c

runScript:
	chmod a+x pythonScript.py

clean:
	rm client server
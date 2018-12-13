CC=gcc
CFLAGS=-Wall

tcps: tcpserver.cpp
	$(CC) -o tcpserver.o tcpserver.cpp wraplib.c wrapsock.c wrapstdio.c wrapunix.c error.c

tcpc: tcpclient.cpp
	$(CC) -o tcpclient.o tcpclient.cpp wraplib.c wrapsock.c wrapstdio.c wrapunix.c error.c

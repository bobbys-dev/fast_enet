CC=g++
CFLAGS=-Wall -ansi

tcps: tcpserver.cpp
	$(CC) -std=c++11 -o tcpserver.o tcpserver.cpp wraplib.c wrapsock.c wrapstdio.c wrapunix.c error.c

tcpc: tcpclient.cpp
	$(CC) -std=c++11 -o tcpclient.o tcpclient.cpp wraplib.c wrapsock.c wrapstdio.c wrapunix.c error.c station_process.cpp 

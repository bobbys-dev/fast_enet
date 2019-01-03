#Fast Ethernet

This project is to simulate the IEEE 802.3u, or Fast Ethernet protocol.
The goal of the project is to practice using Unix BSD and socket API programming through
a multiple-clients-to-server application. The Ethernet protocol is simulated by multiple
processes on multiple machines. Each station in the Ethernet is simulated by
a process.

#Program flow

The StationProcess class (cpp and h files) implements handling of a data_frame struct that essentially represents the event details (source, destination, and dummy data)
The CSMACD header holds the data_frame data structure.
The Client program creates a TCP socket connection to the target server and continues to get next events and either send a dataframe to the specific station (via the Switch) or waits until it receives the specified number of data frames. A special command ‘exit’ will terminate the TCP connection from the client end.
The Server program will initiate and bind a socket to listen to incoming TCP connection requests. It is a blocked listen. When a client TCP connection is requested, it will assign it a number and push it into the array. It will receive dataframes and relay to the appropriate station

#Compiling

All files in the archive shall be extracted into the same directory. Two executables
must be compiled: tcpserver.o and tcpclient.o, which are compile via the commandline
instructions:
`make tcps`
`make tcpo`

#Running

Before running, make note of the IP address of the machine that will run the server (use `ifconfig`).
Run the respective server and client(s) with:
`./tcpserver.o`
`./tcpclient.o <IP address of machine running server>`

Note: multiple clients can be executed to connect to the server with different ssh sessions.

#Input files

Running the client will also instantiate a StationProcess. The StationProcess will
select one of the following event files to read and simulate events.
SPx.in (where x = 0.. 9)

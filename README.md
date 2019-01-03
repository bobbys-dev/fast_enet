#Fast Ethernet
This project is to simulate the IEEE 802.3u, or Fast Ethernet protocol.
The goal of the project is to practice basic socket API programming through
a client/server application. The Ethernet protocol is simulated by multiple
processes on multiple machines. Each station in the Ethernet is simulated by
a process.

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
SP0.in
SP1.in
SP2.in
SP3.in
SP4.in
SP5.in
SP6.in
SP7.in
SP8.in
SP9.in

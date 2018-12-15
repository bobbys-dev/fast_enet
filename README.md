#Fast Ethernet
This project is to simulate the IEEE 802.3u, or Fast Ethernet protocol.
The goal of the project is to practice basic socket API programming through
a client/server application. The Ethernet protocol is simulated by multiple
processes on multiple machines. Each station in the Ethernet is simulated by
a process. The switch of the fast ethernet is also simulated by a process.
Those processes can run on different workstations in the Linux lab.

The IEEE 802.3u protocol, commonly known as the fast Ethernet, is a collision free
protocol and provides a maximum data rate of 100 Mbps. Unlike the classical Ethernet
where stations compete access of the media independently, access to the communication
media in fast Ethernet is controlled by a switch.

#Classical Ethernet vs Fast Ethernet
In contrast to Fast Ethernet, the classic Ethernet, IEEE 802.3 protocol is describe below.

The IEEE 802.3 protocol is a 1-persistent CSMA/CD protocol
([carrier-sense multiple access, collision detection](https://en.wikipedia.org/wiki/Carrier-sense_multiple_access)). It provides a
maximum data rate of 10 Mbps. Stations are connected to a common
communication bus (e.g. carrier) through which communications are carried out.
The basics are:
- A station wishing to send a message frame will first check if the
communication bus before sending out the frame.
- If the bus is busy, the station will wait. If the bus is idle, it will send out the frame.
- A collision occurs when two or more frames from different stations collide on the bus.
- A collision can occur either during the sending period, or the uncertain period (in
which the station has sent out the frame, but is not sure if the frame has arrived
safely to its destination station).
- A station will stop transmission immediately if it detects the collision
during the sending period. It then waits for a random period of time before
trying retransmission (see below).

The random period mentioned above is determined by the well-known binary expo-
nential backoff (BEBO) algorithm:
– After the first collision, the time is divided into discrete slots whose length is
equal to the worst case round-trip propagation time. If tau is the propagation
time for a signal to travel from end to end of the bus, then the roundtrip time
 is 2*tau
 – In general, after the ith collision, where i <= 10, a station will wait for a random
 number of slot times chosen from the interval from 0 to 2^i −1. However, after 10
 collisions, the random interval is fixed between 0 and 2^10 − 1 = 1023 time slots.
 – After 16 collisions, the Ethernet controller for a station suspends retransmissions
 and reports the failure to the data link layer.
– For example, after the first collision, a station waits for either 0,
or 1 time slots before at- tempting its first retransmission. If the first
retransmission collides too, it will wait for either 0, 1, 2, or 3 time
slots before the second retransmission.

#Simulation of Fast Ethernet
Station Process (SP). One station process for each simulated station. For flexibility the
number of such station processes allowed should be a variable. But for implementation
purpose you can assume in the project there are at most 10 station processes, i.e. we
are simulating an Ethernet consisting of at most 10 stations.

Communication Switch Process (CSP). All stations are connected directly to the CSP.
A station, say S1, that wants to send a message to S6 must to the CSP first, which in turn will send the
message to the destination station S6. There is only one CSP, which simulates
the function of a switch in a fast Ethernet.

For every station, the sequence of frames to be sent, together with the destination station
number, is specified as simulation input data file that will be read by that particular station
(confer to Section 3). We assume that frames are of fixed size for simplicity. Each frame has a sequence
number, a source address, a destination address, and a data section.
(1) There are only two types of frames sent by a SP: request frame; and data frame.
(2) There are three frame types sent by the CSP:
– Data frame (forwarded), which has the same format as the one sent by a SP;
– Positive reply, sent in response to a request (to send a data frame) from a SP;
– Negative reply (i.e. reject), sent in response to a request (to send a data frame
frame a SP.

##Multiplexing
Both the CSP and SP have to deal with multiple input events simultaneously. The CSP
must be able to receive request/data frames from multiple SP, send replies, and forward data
frames, at the same time. The SP on the other hand must be able to send data/request
frames, read from input file, and receive data frames sent by other SPs, at the same time. note that the CSP doesn’t care the destination information of a request. Neither the CSP nor the SPs keep a copy of data frame sent out.

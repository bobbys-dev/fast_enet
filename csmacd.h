#ifndef CSMACD_H
#define CSMACD_H
#include <cstdlib>
#include <string>
#include <deque>
#include <fstream>

#define MAX_QUEUE_SIZE 15
//#define MAX_STATIONS 10 // do no use. do not hardcode the SP limit

#define MAX_COLLISIONS 16


namespace CS5310
{
 typedef size_t time_slot;

/**
The CSP maintains two queues: a data frame queue that contains data frames to be
forwarded; and a request frame queue that contains request from SPs for accepting data
frames. Each queue has a fixed size.
**/

/*
Each data frame is a fixed size. It has a sequence number, a source address,
a destination address, and a data section.
*/
struct data_frame {
   int seq;
   int src;
   int dst;
   int data;
   std::string event;
};

/*
request of a station process
*/
struct sp_request {
   int sp_id;
};

/*
Reply of a communication switch process
*/
struct csp_reply {
   int reply;
   int sp_id;
};

struct global_status {
   time_slot current_timeslot;
   int num_stations;
};

void log_event(std::string e, std::string process_name) {
#ifdef COUT_EVENTS
   std::cout << e << std::endl;
#else
   std::ofstream fout;
   std::ifstream fin;
   std::string log_file;
   log_file = process_name + ".log";

   fin.open(log_file);
   fout.open (log_file,std::ios::app); // Append mode
   if (fin.is_open()) {
      fout << e << std::endl; // Writing data to file
   }
   fin.close();
   fout.close(); // Closing the file
 #endif
}

} //end namspece

#endif

#include <cstring>
#include <deque>

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

void create_station_process();
void log_event(string e);
} //end namspece

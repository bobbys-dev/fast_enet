#ifndef STATION_PROCESS_H
#define STATION_PROCESS_H
#include <cstdlib>
#include <fstream>
#include <limits>
#include <time.h>
#include <cmath>
#include <string>
#include "csmacd.h"

/**
StationProcess class.
Operation of a station class operates as such:
(0) If there is a incoming data frame (eg another line in SPx_events.in), receive it.
(1) It reads a line from its simulation input data file and format it as a data frame.
(2) It then sends a request frame to the CSP asking permission to send its data frame
just formatted and wait for reply.
(3) If it gets a reject reply from theh CSP, it has to retransmit the request frame. Your
implementation has to allow a total 3 retransmissions.
(4) If it a positive reply from theh CSP, it will then proceed to send data frame to the
CSP. The SP will not keep a copy of sent frame.
**/
namespace CS5310
{
class StationProcess {

public:

   /**
   *default constructor
   **/
   StationProcess();

   /**
   * returns the station status, which is waiting or sending
   * Precondtion: station exists
   * Postcodition: int representing station status (wait, sending)
   **/
   int get_station_status();

   /**
   * returns the pointer to the event datafrom
   * Precondtion: station exists
   * Postcodition: int representing station status (wait, sending)
   **/
   data_frame* get_next_event();

private:

   int station_address;
   int wait_time;
   int wait_for_n_frames;
   data_frame* df;
   int station_status;
   std::string station_file;
   int next_line; //tracks line in file

   std::fstream& gotoline(std::fstream& file, const int num);

};

}
#endif

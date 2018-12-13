#ifndef STATION_PROCESS_H
#include <cstdlib>

#include "csmacd.h"

namespace CS5310
{
class StationProcess {

public:
   typedef size_t wait_interval;
   typddef int station_status;
   /**
   *default constructor
   **/
   StationProcess();

   /**
   * Precondtion: must have had at least 1 collision but less than 16
   * Postcodition: unsigned int returned to tell station to wait for that interval
   **/
   wait_interval get_bebo_time (const size_t ith_collision);

   /**
   * Precondtion: station exists
   * Postcodition: int representing station status (wait, sending, collided)
   **/
   station_status get_station_status(const int station_address);
   data_frame* get_data_frame(const int station_address);

private:
   int station_address;
   size_t wait_time;
   data_frame* df;
   int status;
};

}
#endif

#include "station_process.h"
#include <iostream> //for debug

namespace CS5310
{

   /*
   * constructor uses seed to generate different time intervals than peers
   *new instance is randomly assigned a file to read events from
   *initialize all private member variables
   *
   */
   StationProcess::StationProcess() {

      /* Intializes random number generator for backofftime*/
      srand((unsigned) time(0));

      /**/
      std::string spn = std::to_string(rand()%10); // assuming max of 10 variations
      this->station_file = "SP" + spn + "_events.in";
      std::cout << "Create SP pointing to " << station_file << std::endl;
      this->next_line = 0;
      this->wait_for_n_frames = 0;
      this->station_address = rand() % 999 + 1001;
      this->df = new data_frame;
      std::cout << "My station address is " << this->station_address << std::endl;
   }

   int StationProcess::get_bebo_time (const int ith_collision) {
      int max;

      if (ith_collision <= 10) {
         //max is 2^i - 1
         max = (int)pow(2,ith_collision) - 1;

      } else {
         //max is 2^10 - 1
         max = (int)pow(2,10) - 1;
      }
      return rand() % (max + 1);
   }

   int StationProcess::get_station_status(const int station_address) {
      return this->station_status;
   }

   data_frame* StationProcess::get_data_frame(const int station_address) {

          std::fstream file(station_file);

         this->gotoline(file, next_line);

          std::string event;
          getline(file,event); // get entire event line in file

          //limit of search is 2 digits
         if (event.find("Waiting") == 0) {
            wait_for_n_frames = stoi(event.substr(event.find("Wait")+19,2));
         } else {
            if(event.find("Frame") != std::string::npos) {
               df->seq =  stoi(event.substr(event.find(" ")+1,2));
               std::cout << "frame seq is:"<< df->seq << std::endl;
            }
            if(event.find("To SP") != std::string::npos) {
               df->dst =  stoi(event.substr(event.find("SP ")+3,2));
                std::cout << "target is:"<< df->dst << std::endl;
            }
            df->src = this->station_address;
            df->data = 7777;
         }
         return df;
   }

   std::fstream& StationProcess::gotoline(std::fstream& file, const int num) {
      if (file.is_open()) {
         file.seekg(std::ios::beg);
         for(int i=0; i < num - 1; ++i){
            file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
         }
      } else {
         std::cout << "failed to open file" << '\n';
      }
      return file;
   }
}

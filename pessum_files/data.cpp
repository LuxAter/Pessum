#include "data.hpp"
#include "datapoint.hpp"
#include <vector>
#include <string>
#include <fstream>
#include "log.hpp"

std::vector<pessum::DataPoint> pessum::Load(std::string file){
  std::vector<DataPoint> data;
  std::ifstream load(file.c_str());
  if(load.is_open()){
    std::string line;
    while(getline(load, line)){
      data.push_back(pessum::Make_DataPoint(line));
    }
  }else{
    pessum::Log(pessum::WARNING, "Failed to open data file %s", "pessum::Load", file.c_str());
  }
  return(data);
}

void pessum::Save(std::string file, std::vector<DataPoint> data){
  std::ofstream save(file.c_str());
  if(save.is_open()){
    for(int i = 0; i < data.size(); i++){
      if(data[i].type == PESSUM_INT){
        save << data[i].i << "\n";
      } else if(data[i].type == PESSUM_DOUBLE){
        save << data[i].d << "\n"; 
      } else if(data[i].type == PESSUM_STR){
        save << data[i].s << "\n";
      } else if(data[i].type == PESSUM_BOOL){
        if(data[i].b == true){
          save << "true\n";
        }else if(data[i].b == false){
          save << "false\n";
        }
      }
    }
  }else{
    Log(WARNING, "Failed to open data file %s", "pessum::Save", file.c_str());
  }
}

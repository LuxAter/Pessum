#include <fstream>
#include <string>
#include <vector>
#include "data.hpp"
#include "datapoint.hpp"
#include "log.hpp"

std::vector<pessum::DataPoint> pessum::Load(std::string file) {
  std::vector<DataPoint> data;
  std::ifstream load(file.c_str());
  if (load.is_open()) {
    std::string line;
    while (getline(load, line)) {
      data.push_back(pessum::Make_DataPoint(line));
    }
  } else {
    pessum::Log(pessum::WARNING, "Failed to open data file %s", "pessum::Load",
                file.c_str());
  }
  return (data);
}

void pessum::Save(std::string file, std::vector<DataPoint> data) {
  std::ofstream save(file.c_str());
  if (save.is_open()) {
    for (int i = 0; i < data.size(); i++) {
      if (data[i].type == PESSUM_INT) {
        save << data[i].int_value << "\n";
      } else if (data[i].type == PESSUM_DOUBLE) {
        save << data[i].double_value << "\n";
      } else if (data[i].type == PESSUM_STR) {
        save << data[i].string_value << "\n";
      } else if (data[i].type == PESSUM_BOOL) {
        if (data[i].bool_value == true) {
          save << "true\n";
        } else if (data[i].bool_value == false) {
          save << "false\n";
        }
      }
    }
  } else {
    Log(WARNING, "Failed to open data file %s", "pessum::Save", file.c_str());
  }
}

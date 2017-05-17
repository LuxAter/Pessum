#ifndef PESSUM_DATA_HPP
#define PESSUM_DATA_HPP
#include <vector>
#include <string>
#include "datapoint.hpp"
namespace pessum{
  std::vector<DataPoint> Load(std::string file);
  void Save(std::string file, std::vector<DataPoint> data);
};
#endif

#include "yaml_file.hpp"

#include <fstream>

#include "../log/log.hpp"
#include "yaml.hpp"

void pessum::yaml::SaveToFile(Node yaml, std::string file_path) {
  std::ofstream out(file_path.c_str());
  if (out.is_open()) {
    out << yaml;
    out.close();
  } else {
    Log(ERROR, "Failed to open file %s", "pessum::yaml::SaveToFile",
        file_path.c_str());
  }
}

pessum::yaml::Node pessum::yaml::LoadFromFile(std::string file_path) {
  Node yaml;
  std::ifstream in(file_path.c_str());
  if (in.is_open()) {
    std::string line;
    while (getline(in, line)) {
    }
  } else {
    Log(WARNING, "Failed to open file %s", "pessum::yaml::LoadFromFile",
        file_path.c_str());
  }
  return yaml;
}

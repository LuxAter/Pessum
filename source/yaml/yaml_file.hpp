#ifndef PESSUM_YAML_FILE_HPP
#define PESSUM_YAML_FILE_HPP
#include "yaml.hpp"

namespace pessum {
  namespace yaml {
    void SaveToFile(Node yaml, std::string file_path);
    Node LoadFromFile(std::string file_path);
  }  // namespace yaml
}  // namespace pessum
#endif /* ifndef PESSUM_YAML_FILE_HPP */

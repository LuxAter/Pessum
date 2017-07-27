#ifndef PESSUM_YAML_FILE_HPP
#define PESSUM_YAML_FILE_HPP
#include "yaml.hpp"

#include <string>
#include <vector>

namespace pessum {
  namespace yaml {
    void SaveToFile(Node yaml, std::string file_path);
    Node LoadFromFile(std::string file_path);
    Node LoadChunk(std::vector<std::string> str);
    Node SetValue(std::string str);
    int TrimString(std::string& str, std::string character = " ");
    int GetIndent(std::string str);
    void TrimIndent(std::string& str, int limit = -1,
                    std::string character = " ");
  }  // namespace yaml
}  // namespace pessum
#endif /* ifndef PESSUM_YAML_FILE_HPP */

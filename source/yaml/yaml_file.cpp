#include "yaml_file.hpp"

#include <iostream>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>

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
    std::vector<std::string> lines;
    std::string line;
    while (getline(in, line)) {
      lines.push_back(line);
    }
    yaml = LoadChunk(lines);
    in.close();
  } else {
    Log(WARNING, "Failed to open file %s", "pessum::yaml::LoadFromFile",
        file_path.c_str());
  }
  return yaml;
}

pessum::yaml::Node pessum::yaml::LoadChunk(std::vector<std::string> str) {
  Node yaml;
  for (int i = 0; i < str.size(); i++) {
    std::stringstream ss(str[i]);
    std::string name, value;
    getline(ss, name, ':');
    getline(ss, value);
    if (value == std::string()) {
      std::vector<std::string> sub_set;
      i++;
      int step = 2;
      if (i < str.size()) {
        GetIndent(str[i]);
      }
      while (i < str.size() && GetIndent(str[i]) >= step) {
        TrimIndent(str[i], step);
        sub_set.push_back(str[i]);
        i++;
      }
      i--;
      TrimString(name);
      Node chunk = LoadChunk(sub_set);
      if (name.size() > 2 && name[0] == '-' && name[1] == ' ') {
        name.erase(name.begin(), name.begin() + 2);
        if (chunk.valid() == true) {
          Node sub_chunk;
          sub_chunk.push_back(name, chunk);
          yaml.push_back(sub_chunk);
        } else {
          yaml.push_back(name);
        }
      } else {
        yaml[name] = chunk;
      }
    } else {
      TrimString(name);
      TrimString(value);
      yaml[name] = SetValue(value);
    }
  }
  return yaml;
}

pessum::yaml::Node pessum::yaml::SetValue(std::string str) {
  Node yaml;
  bool is_bool = false;
  if (str == "true" || str == "True" || str == "TRUE") {
    yaml = true;
    is_bool = true;
  } else if (str == "false" || str == "False" || str == "FALSE") {
    yaml = false;
    is_bool = true;
  }
  if (is_bool == false) {
    bool is_int = true;
    bool has_dot = false;
    for (int i = 0; i < str.size() && is_int == true; i++) {
      if (i == 0 && str[i] == '-') {
      } else if (str[i] == '.' && has_dot == false) {
        has_dot = true;
      } else if (str[i] == '.' && has_dot == true) {
        is_int = false;
      } else if (int(str[i]) > 57 || int(str[i]) < 48) {
        is_int = false;
      }
    }
    if (is_int == true && has_dot == true) {
      yaml = stod(str);
    } else if (is_int == true && has_dot == false) {
      yaml = stoi(str);
    } else if (is_int == false) {
      yaml = str;
    }
  }
  return yaml;
}

int pessum::yaml::TrimString(std::string& str, std::string character) {
  size_t str_begin = str.find_first_not_of(character);
  size_t str_end = str.find_last_not_of(character);
  std::string trimed = str.substr(str_begin, str_end - str_begin + 1);
  int diff = str.size() - trimed.size();
  str = trimed;
  return diff;
}

int pessum::yaml::GetIndent(std::string str) {
  std::string::iterator first_non_space = std::find_if(
      str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(isspace)));
  int count = std::distance(str.begin(), first_non_space);
  return count;
}

void pessum::yaml::TrimIndent(std::string& str, int limit,
                              std::string character) {
  size_t str_begin = str.find_first_not_of(character);
  if (limit != -1) {
    if (str_begin > limit) {
      str_begin = limit;
    }
  }
  str = str.substr(str_begin, str.size() - str_begin + 1);
}

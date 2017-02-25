#include "../logging/logging.hpp"
#include "luxreader.hpp"
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

std::vector<pessum::luxreader::Item>
pessum::luxreader::LoadLuxFile(std::string filepath) {
  std::vector<Item> filecontents;
  std::vector<std::string> rawstrings;
  std::ifstream file(filepath.c_str());
  if (file.is_open()) {
    std::string line = "";
    while (getline(file, line)) {
      rawstrings.push_back(line);
    }
    file.close();
  } else {
    logging::Log("w;Failed to open " + filepath +
                 ";pessum/luxreader/LoadLuxFile");
  }
  for (int i = 0; i < rawstrings.size(); i++) {
    Item newitem;
    newitem.typeindex = FindType(rawstrings[i]);
    if (newitem.typeindex == 0) {
      newitem.b = false;
    } else if (newitem.typeindex == 1) {
      newitem.i = 0;
    } else if (newitem.typeindex == 2) {
      newitem.d = 0.0;
    } else if (newitem.typeindex == 3) {
      newitem.s = "";
    } else if (newitem.typeindex == 4) {
    } else if (newitem.typeindex == 5) {
    } else if (newitem.typeindex == 6) {
    } else if (newitem.typeindex == 7) {
    }
  }
  return (filecontents);
}

int pessum::luxreader::FindType(std::string str) {
  int type = 0;
  return (type);
}

std::string pessum::luxreader::MakeCaps(std::string str) {
  for (int i = 0; i < str.size(); i++) {
    if (int(str[i]) >= 97 && int(str[i]) <= 122) {
      str[i] = char(int(str[i]) - 32);
    }
  }
  return (str);
}

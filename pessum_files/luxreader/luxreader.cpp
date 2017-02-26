#include "../logging/logging.hpp"
#include "luxreader.hpp"
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

int pessum::luxreader::FindType(std::string str) {
  int type = 0;
  bool list = false;
  if (str.size() == 0) {
    return (-1);
  }
  if (str[0] == '{') {
    list = true;
  }
  for (int i = 0 + list; i < str.size() - list; i++) {
    if (list == true && str.size() != i + 1 && str[i] == ',' &&
        str[i + 1] == ' ') {
      i += 2;
    }
    int charint = int(str[i]);
    std::string falsecheck, truecheck;
    if (str.size() >= i + 5) {
      falsecheck = std::string(str.begin() + i, str.begin() + i + 5);
    }
    if (str.size() >= i + 4) {
      truecheck = std::string(str.begin() + i, str.begin() + i + 4);
    }
    if (falsecheck == "false" && type == 0) {
      type = 0;
      i += 4;
    } else if (truecheck == "true" && type == 0) {
      type = 0;
      i += 3;
    } else if (charint >= 48 && charint <= 57 && type <= 1) {
      type = 1;
    } else if (((charint >= 48 && charint <= 57) || charint == 46) &&
               type <= 2) {
      type = 2;
    } else if (type <= 3) {
      type = 3;
    }
  }
  if (list == true) {
    type += 4;
  }
  return (type);
}

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
      if (rawstrings[i] == "false") {
        newitem.b = false;
      } else if (rawstrings[i] == "true") {
        newitem.b = true;
      }
    } else if (newitem.typeindex == 1) {
      newitem.i = stoi(rawstrings[i]);
    } else if (newitem.typeindex == 2) {
      newitem.d = stod(rawstrings[i]);
    } else if (newitem.typeindex == 3) {
      newitem.s = rawstrings[i];
    } else if (newitem.typeindex == 4) {
      std::string substring = "";
      for (int j = 1; j < rawstrings[i].size() - 1; j++) {
        if (rawstrings[i][j] == ',' && rawstrings[i][j + 1] == ' ') {
          if (substring == "false") {
            newitem.vb.push_back(false);
          } else if (substring == "true") {
            newitem.vb.push_back(true);
          }
          substring = "";
        } else {
          substring += rawstrings[i][j];
        }
      }
    } else if (newitem.typeindex == 5) {
      std::string substring = "";
      for (int j = 1; j < rawstrings[i].size() - 1; j++) {
        if (rawstrings[i][j] == ',' && rawstrings[i][j + 1] == ' ') {
          newitem.vi.push_back(stoi(substring));
          substring = "";
        } else {
          substring += rawstrings[i][j];
        }
      }
    } else if (newitem.typeindex == 6) {
      std::string substring = "";
      for (int j = 1; j < rawstrings[i].size() - 1; j++) {
        if (rawstrings[i][j] == ',' && rawstrings[i][j + 1] == ' ') {
          newitem.vd.push_back(stod(substring));
          substring = "";
        } else {
          substring += rawstrings[i][j];
        }
      }
    } else if (newitem.typeindex == 7) {
      std::string substring = "";
      for (int j = 1; j < rawstrings[i].size() - 1; j++) {
        if (rawstrings[i][j] == ',' && rawstrings[i][j + 1] == ' ') {
          newitem.vs.push_back(substring);
          substring = "";
        } else {
          substring += rawstrings[i][j];
        }
      }
    }
    filecontents.push_back(newitem);
  }
  return (filecontents);
}

void pessum::luxreader::SaveLuxFile(std::string filepath,
                                    std::vector<Item> contents) {}

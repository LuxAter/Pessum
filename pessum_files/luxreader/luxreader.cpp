#include "../logging/logging.hpp"
#include "luxreader.hpp"
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

pessum::luxreader::Item pessum::luxreader::CreateItem(bool val) {
  Item newitem;
  newitem.typeindex = 0;
  newitem.b = val;
  return (newitem);
}

pessum::luxreader::Item pessum::luxreader::CreateItem(int val) {
  Item newitem;
  newitem.typeindex = 1;
  newitem.i = val;
  return (newitem);
}

pessum::luxreader::Item pessum::luxreader::CreateItem(double val) {
  Item newitem;
  newitem.typeindex = 2;
  newitem.d = val;
  return (newitem);
}

pessum::luxreader::Item pessum::luxreader::CreateItem(std::string val) {
  Item newitem;
  newitem.typeindex = 3;
  newitem.s = val;
  return (newitem);
}

pessum::luxreader::Item pessum::luxreader::CreateItem(std::vector<bool> vec) {
  Item newitem;
  newitem.typeindex = 4;
  newitem.vb = vec;
  return (newitem);
}

pessum::luxreader::Item pessum::luxreader::CreateItem(std::vector<int> vec) {
  Item newitem;
  newitem.typeindex = 5;
  newitem.vi = vec;
  return (newitem);
}

pessum::luxreader::Item pessum::luxreader::CreateItem(std::vector<double> vec) {
  Item newitem;
  newitem.typeindex = 6;
  newitem.vd = vec;
  return (newitem);
}

pessum::luxreader::Item
pessum::luxreader::CreateItem(std::vector<std::string> vec) {
  Item newitem;
  newitem.typeindex = 7;
  newitem.vs = vec;
  return (newitem);
}

pessum::luxreader::Item pessum::luxreader::CreateItemStr(std::string str) {
  Item newitem;
  newitem.typeindex = FindType(str);
  if (newitem.typeindex == 0) {
    if (str == "false") {
      newitem.b = false;
    } else if (str == "true") {
      newitem.b = true;
    }
  } else if (newitem.typeindex == 1) {
    newitem.i = stoi(str);
  } else if (newitem.typeindex == 2) {
    newitem.d = stod(str);
  } else if (newitem.typeindex == 3) {
    newitem.s = str;
  } else if (newitem.typeindex >= 4) {
    std::string substring = "";
    for (int j = 1; j < str.size() - 1; j++) {
      if (str[j] == ',' && str[j + 1] == ' ') {
        if (newitem.typeindex == 4) {
          if (substring == "false") {
            newitem.vb.push_back(false);
          } else if (substring == "true") {
            newitem.vb.push_back(true);
          }
        } else if (newitem.typeindex == 5) {
          newitem.vi.push_back(stoi(substring));
        } else if (newitem.typeindex == 6) {
          newitem.vd.push_back(stod(substring));
        } else if (newitem.typeindex == 7) {
          newitem.vs.push_back(substring);
        }
        substring = "";
      } else {
        substring += str[j];
      }
    }
    if (newitem.typeindex == 4) {
      if (substring == "false") {
        newitem.vb.push_back(false);
      } else if (substring == "true") {
        newitem.vb.push_back(true);
      }
    } else if (newitem.typeindex == 5) {
      newitem.vi.push_back(stoi(substring));
    } else if (newitem.typeindex == 6) {
      newitem.vd.push_back(stod(substring));
    } else if (newitem.typeindex == 7) {
      newitem.vs.push_back(substring);
    }
  }
  return (newitem);
}

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
    filecontents.push_back(CreateItemStr(rawstrings[i]));
  }
  return (filecontents);
}

void pessum::luxreader::SaveLuxFile(std::string filepath,
                                    std::vector<Item> contents) {
  std::ofstream luxfile(filepath.c_str());
  if (luxfile.is_open()) {
    for (int i = 0; i < contents.size(); i++) {
      if (contents[i].typeindex == 0) {
        if (contents[i].b == false) {
          luxfile << "false";
        } else if (contents[i].b == true) {
          luxfile << "true";
        }
      } else if (contents[i].typeindex == 1) {
        luxfile << contents[i].i;
      } else if (contents[i].typeindex == 2) {
        luxfile << contents[i].d;
      } else if (contents[i].typeindex == 3) {
        luxfile << contents[i].s;
      } else if (contents[i].typeindex == 4) {
        luxfile << "{";
        for (int j = 0; j < contents[i].vb.size(); j++) {
          if (contents[i].vb[j] == false) {
            luxfile << "false";
          } else if (contents[i].vb[j] == true) {
            luxfile << "true";
          }
          if (j != contents[i].vb.size() - 1) {
            luxfile << ", ";
          }
        }
        luxfile << "}";
      } else if (contents[i].typeindex == 5) {
        luxfile << "{";
        for (int j = 0; j < contents[i].vi.size(); j++) {
          luxfile << contents[i].vi[j];
          if (j != contents[i].vi.size() - 1) {
            luxfile << ", ";
          }
        }
        luxfile << "}";
      } else if (contents[i].typeindex == 6) {
        luxfile << "{";
        for (int j = 0; j < contents[i].vd.size(); j++) {
          luxfile << contents[i].vd[j];
          if (j != contents[i].vd.size() - 1) {
            luxfile << ", ";
          }
        }
        luxfile << "}";
      } else if (contents[i].typeindex == 7) {
        luxfile << "{";
        for (int j = 0; j < contents[i].vs.size(); j++) {
          luxfile << contents[i].vs[j];
          if (j != contents[i].vs.size() - 1) {
            luxfile << ", ";
          }
        }
        luxfile << "}";
      }
      luxfile << "\n";
    }
  } else {
    logging::Log("w;Failed to open " + filepath +
                 ";pessum/luxreader/SaveLuxFile");
  }
}

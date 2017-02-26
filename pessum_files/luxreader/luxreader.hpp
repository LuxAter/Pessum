#ifndef PESSUM_LUXREADER_LUXREADER_HPP
#define PESSUM_LUXREADER_LUXREADER_HPP
#include <string>
#include <vector>
namespace pessum {
namespace luxreader {
struct Item {
  int typeindex = 0;
  bool b = false;
  int i = 0;
  double d = 0.0;
  std::string s = "";
  std::vector<bool> vb;
  std::vector<int> vi;
  std::vector<double> vd;
  std::vector<std::string> vs;
};
int FindType(std::string str);
std::vector<Item> LoadLuxFile(std::string filepath);
void SaveLuxFile(std::string filepath, std::vector<Item> contents);
}
}
#endif

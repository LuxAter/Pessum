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
Item CreateItem(bool val);
Item CreateItem(int val);
Item CreateItem(double val);
Item CreateItem(std::string val);
Item CreateItem(std::vector<bool> vec);
Item CreateItem(std::vector<int> vec);
Item CreateItem(std::vector<double> vec);
Item CreateItem(std::vector<std::string> vec);
Item CreateItemStr(std::string str);
int FindType(std::string str);
std::vector<Item> LoadLuxFile(std::string filepath);
void SaveLuxFile(std::string filepath, std::vector<Item> contents);
}
}
#endif

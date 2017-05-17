#ifndef PESSUM_DATAPOINT_HPP
#define PESSUM_DATAPOINT_HPP
#include <string>
namespace pessum{
  enum PessumDataType{
    PESSUM_NONE,
    PESSUM_INT,
    PESSUM_DOUBLE,
    PESSUM_STR,
    PESSUM_BOOL
  };
  struct DataPoint{
    DataPoint();  
    DataPoint(int v);
      DataPoint(double v);
      DataPoint(std::string v);
      DataPoint(bool v);
      int i, type;
      double d;
      std::string s;
      bool b;
  };
  DataPoint Make_DataPoint(std::string str);
}
#endif

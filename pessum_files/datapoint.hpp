#ifndef PESSUM_DATAPOINT_HPP
#define PESSUM_DATAPOINT_HPP
#include <string>
namespace pessum {
  enum PessumDataType {
    PESSUM_NONE,
    PESSUM_INT,
    PESSUM_DOUBLE,
    PESSUM_STR,
    PESSUM_BOOL
  };
  class DataPoint {
   public:
    DataPoint();
    DataPoint(int value);
    DataPoint(double value);
    DataPoint(std::string value);
    DataPoint(bool value);

    int int_value, type;
    double double_value;
    std::string string_value;
    bool bool_value;
  };
  DataPoint Make_DataPoint(std::string str);
}
#endif

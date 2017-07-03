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
    explicit DataPoint();
    explicit DataPoint(int value);
    explicit DataPoint(double value);
    explicit DataPoint(std::string value);
    explicit DataPoint(const char* value);
    explicit DataPoint(bool value);

    void operator=(int value);
    void operator=(double value);
    void operator=(std::string value);
    void operator=(const char* value);
    void operator=(bool value);

    operator int();
    operator double();
    operator std::string();
    operator bool();

    int int_value = int(), type = PESSUM_NONE;
    double double_value = double();
    std::string string_value = std::string();
    bool bool_value = bool();
  };
  DataPoint Make_DataPoint(std::string str);
}
#endif

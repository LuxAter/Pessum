#include "datapoint.hpp"
#include <string>

pessum::DataPoint::DataPoint() { type = PESSUM_NONE; }

pessum::DataPoint::DataPoint(int value) {
  int_value = value;
  type = PESSUM_INT;
}

pessum::DataPoint::DataPoint(double value) {
  double_value = value;
  type = PESSUM_DOUBLE;
}

pessum::DataPoint::DataPoint(std::string value) {
  string_value = value;
  type = PESSUM_STR;
}

pessum::DataPoint::DataPoint(const char* value) {
  string_value = std::string(value);
  type = PESSUM_STR;
}

pessum::DataPoint::DataPoint(bool value) {
  bool_value = value;
  type = PESSUM_BOOL;
}

void pessum::DataPoint::operator=(int value) {
  int_value = value;
  type = PESSUM_INT;
}

void pessum::DataPoint::operator=(double value) {
  double_value = value;
  type = PESSUM_DOUBLE;
}

void pessum::DataPoint::operator=(std::string value) {
  string_value = value;
  type = PESSUM_STR;
}

void pessum::DataPoint::operator=(const char* value) {
  string_value = std::string(value);
  type = PESSUM_STR;
}

void pessum::DataPoint::operator=(bool value) {
  bool_value = value;
  type = PESSUM_BOOL;
}

pessum::DataPoint::operator int() { return int_value; }

pessum::DataPoint::operator bool() { return bool_value; }

pessum::DataPoint::operator double() { return double_value; }

pessum::DataPoint::operator std::string() { return string_value; }

pessum::DataPoint pessum::Make_DataPoint(std::string str) {
  DataPoint return_data;
  if (str == "true") {
    return_data = DataPoint(true);
  } else if (str == "false") {
    return_data = DataPoint(false);
  } else {
    bool alpha = false, point = false;
    for (int i = 0; i < str.size() && alpha == false; i++) {
      if ((int(str[i]) > 57 || int(str[i]) < 48) && int(str[i]) != 46) {
        alpha = true;
      } else if (int(str[i]) == 46) {
        if (point == false) {
          point = true;
        } else if (point == true) {
          point = false;
          alpha = true;
        }
      }
    }
    if (alpha == true) {
      return_data = DataPoint(str);
    } else if (point == true) {
      return_data = DataPoint(stod(str));
    } else {
      return_data = DataPoint(stoi(str));
    }
  }
  return (return_data);
}

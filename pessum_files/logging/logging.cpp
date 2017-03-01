#include "logging.hpp"
#include <ctime>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
namespace pessum {
namespace logging {
bool devmode = false, logtimes = false;
std::ofstream logoutputfile;
std::vector<std::tuple<std::string, int, std::string>> loglocationbindings;
}
}

int pessum::logging::AddLogLocation(std::string locationstring) {
  std::string newstr;
  std::string abbrev = "";
  int counter = 3;
  for (int i = 0; i < newstr.size(); i++) {
    if (newstr[i] != '/' && newstr[i] != '\\' && counter > 0) {
      counter--;
      abbrev += newstr[i];
    } else if (newstr[i] == '/' || newstr[i] == '\\') {
      counter = 3;
      abbrev += '/';
    }
  }
  std::tuple<std::string, int, std::string> location(
      locationstring, loglocationbindings.size(), abbrev);
  loglocationbindings.push_back(location);
  return (std::get<1>(location));
}

std::string pessum::logging::GetLocation(int index) {
  for (int i = 0; i < loglocationbindings.size(); i++) {
    if (index == std::get<1>(loglocationbindings[i])) {
      return (std::get<0>(loglocationbindings[i]));
    }
  }
  return (std::to_string(index));
}

std::string pessum::logging::GetLocation(std::string str) {
  std::string newstr = RemoveCaps(str);
  for (int i = 0; i < loglocationbindings.size(); i++) {
    if (newstr == std::get<2>(loglocationbindings[i])) {
      return (std::get<0>(loglocationbindings[i]));
    }
  }
  return (str);
}

std::string pessum::logging::GetType(std::string str) {
  for (int i = 0; i < str.size(); i++) {
    if (int(str[i]) >= 97 && int(str[i]) <= 122) {
      str[i] = char(int(str[i]) - 32);
    }
  }
  if (str == "F") {
    str = "FATAL";
  } else if (str == "E") {
    str = "ERROR";
  } else if (str == "W") {
    str = "WARNING";
  } else if (str == "I") {
    str = "INFO";
  } else if (str == "D") {
    str = "DEBUG";
  } else if (str == "T") {
    str = "TRACE";
  } else if (str == "S") {
    str = "SUCCESS";
  } else if (str == "G") {
    str = "GOOD";
  } else if (str == "C") {
    str = "COMMENT";
  }
  return (str);
}

void pessum::logging::Log(std::string str) {
  std::string typestr, logstr, locationstr, functionstr;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == ';') {
      typestr = std::string(str.begin(), str.begin() + i);
      str.erase(str.begin(), str.begin() + i + 1);
      break;
    }
  }
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == ';') {
      logstr = std::string(str.begin(), str.begin() + i);
      str.erase(str.begin(), str.begin() + i + 1);
      break;
    }
  }
  for (int i = str.size() - 1; i >= 0; i--) {
    if (str[i] == '/' || str[i] == '\\' || str[i] == ';') {
      functionstr = std::string(str.begin() + i + 1, str.end());
      str.erase(str.begin() + i, str.end());
      break;
    }
  }
  locationstr = str;
  Log(typestr, logstr, locationstr, functionstr);
}

void pessum::logging::Log(std::string typelogstr, std::string locationstr) {
  std::string logstr = "";
  for (int i = 0; i < typelogstr.size(); i++) {
    if (typelogstr[i] == ';') {
      logstr = std::string(typelogstr.begin() + i + 1, typelogstr.end());
      typelogstr.erase(typelogstr.begin() + i, typelogstr.end());
      break;
    }
  }
  std::string functionstr = "";
  for (int i = locationstr.size() - 1; i >= 0; i--) {
    if (locationstr[i] == '/' || locationstr[i] == '\\' ||
        locationstr[i] == ';') {
      functionstr = std::string(locationstr.begin() + i + 1, locationstr.end());
      locationstr.erase(locationstr.begin() + i, locationstr.end());
      break;
    }
  }
  Log(typelogstr, logstr, locationstr, functionstr);
}

void pessum::logging::Log(std::string typelogstr, int locationindex,
                          std::string funcitonstr) {
  std::string logstr = "";
  for (int i = 0; i < typelogstr.size(); i++) {
    if (typelogstr[i] == ';') {
      logstr = std::string(typelogstr.begin() + i + 1, typelogstr.end());
      typelogstr.erase(typelogstr.begin() + i, typelogstr.end());
      break;
    }
  }
  Log(typelogstr, logstr, locationindex, funcitonstr);
}

void pessum::logging::Log(std::string typestr, std::string logstr,
                          std::string locationstr) {
  std::string functionstr = "";
  for (int i = locationstr.size() - 1; i >= 0; i--) {
    if (locationstr[i] == '/' || locationstr[i] == '\\' ||
        locationstr[i] == ';') {
      functionstr = std::string(locationstr.begin() + i + 1, locationstr.end());
      locationstr.erase(locationstr.begin() + i, locationstr.end());
      break;
    }
  }
  Log(typestr, logstr, locationstr, functionstr);
}

void pessum::logging::Log(std::string typestr, std::string logstr,
                          int locationindex, std::string functionstr) {
  Log(typestr, logstr, GetLocation(locationindex), functionstr);
}

void pessum::logging::Log(std::string typestr, std::string logstr,
                          std::string locationstr, std::string functionstr) {
  typestr = GetType(typestr);
  std::string logfileline = "<" + typestr + ">{" + GetLocation(locationstr) +
                            "}{" + functionstr + "}" + logstr;
  if (logtimes == true) {
    time_t currenttime;
    time(&currenttime);
    std::string logtime = ctime(&currenttime);
    logtime.erase(logtime.begin(), logtime.begin() + 11);
    logtime.erase(logtime.end() - 6, logtime.end());
    logfileline = "[" + logtime + "]" + logfileline;
  }
  if (logoutputfile.is_open()) {
    if (devmode == true ||
        (typestr == "FATAL" || typestr == "ERROR" || typestr == "WARNING")) {
      logoutputfile << logfileline << "\n";
    }
  }
}

void pessum::logging::LogTimeStamp(bool date) {
  time_t currenttime;
  time(&currenttime);
  std::string logtime = ctime(&currenttime);
  logtime.erase(logtime.end() - 1);
  if (date == false) {
    logtime.erase(logtime.begin(), logtime.begin() + 11);
    logtime.erase(logtime.end() - 6, logtime.end());
  }
  Log("time", logtime, "TimeStamp");
}

void pessum::logging::InitializeLogging(std::string outputfile, bool recordtime,
                                        bool dev) {
  devmode = dev;
  logtimes = recordtime;
  logoutputfile.open(outputfile.c_str(), std::ios::out);
  if (logoutputfile.is_open()) {
    LogTimeStamp(true);
    Log("info", "Opened Log File " + outputfile,
        "pessum/logging/InitializeLogging");
  }
}

std::string pessum::logging::RemoveCaps(std::string str) {
  for (int i = 0; i < str.size(); i++) {
    if (int(str[i]) >= 65 && int(str[i]) <= 90) {
      str[i] = char(int(str[i]) + 32);
    }
  }
  return (str);
}

void pessum::logging::TerminateLogging() {
  if (logoutputfile.is_open()) {
    Log("info", "Terminated Log File", "pessum/logging/TerminatedLogging");
    LogTimeStamp(true);
    logoutputfile.close();
  }
  loglocationbindings.clear();
}

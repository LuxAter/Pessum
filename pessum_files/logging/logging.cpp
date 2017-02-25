#include "logging.hpp"
#include <ctime>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
namespace pessum {
namespace logging {
std::ofstream logoutputfile;
std::vector<std::tuple<std::string, int, std::string>> loglocationbindings;
bool devmode = false, logtimes = false;
}
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

void pessum::logging::TerminateLogging() {
  if (logoutputfile.is_open()) {
    Log("info;Terminated Log File;pessum/logging/TerminatedLogging");
    LogTimeStamp(true);
    logoutputfile.close();
  }
  loglocationbindings.clear();
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

void pessum::logging::Log(std::string typestr, std::string logstr,
                          std::string locationstr, std::string functionstr) {
  if (logstr.size() == 0) {
    for (int i = 0; i < typestr.size(); i++) {
      if (typestr[i] == ';') {
        logstr = std::string(typestr.begin() + i + 1, typestr.end());
        typestr.erase(typestr.begin() + i, typestr.end());
        break;
      }
    }
  }
  if (locationstr.size() == 0) {
    for (int i = 0; i < logstr.size(); i++) {
      if (logstr[i] == ';') {
        locationstr = std::string(logstr.begin() + i + 1, logstr.end());
        logstr.erase(logstr.begin() + i, logstr.end());
        break;
      }
    }
  }
  if (functionstr.size() == 0) {
    for (int i = locationstr.size() - 1; i >= 0; i--) {
      if (locationstr[i] == '/' || locationstr[i] == '\\' ||
          locationstr[i] == ';') {
        functionstr =
            std::string(locationstr.begin() + i + 1, locationstr.end());
        locationstr.erase(locationstr.begin() + i, locationstr.end());
        break;
      }
    }
  }
  std::string logfileline = "";
  if (logtimes == true) {
    time_t currenttime;
    time(&currenttime);
    logfileline = ctime(&currenttime);
    logfileline.erase(logfileline.begin(), logfileline.begin() + 11);
    logfileline.erase(logfileline.end() - 6, logfileline.end());
    logfileline = "[" + logfileline + "]";
  }
  typestr = GetType(typestr);
  logfileline += "<" + typestr + ">";
  logfileline += "{" + GetLocation(locationstr) + "}";
  logfileline += "{" + functionstr + "}";
  logfileline += logstr;
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

std::string pessum::logging::RemoveCaps(std::string str) {
  for (int i = 0; i < str.size(); i++) {
    if (int(str[i]) >= 65 && int(str[i]) <= 90) {
      str[i] = char(int(str[i]) + 32);
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

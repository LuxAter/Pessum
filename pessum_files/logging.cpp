#include "logging.h"
#include "pessum_core.h"
#include <ctime>
#include <fstream>
#include <string>

namespace pessum {
namespace logging {
std::ofstream logfile;
std::vector<std::string> loglocationbindings;
bool devmode = 0;
}
}

bool pessum::logging::InitializeLogging(std::string outputfile, bool dev) {
  devmode = dev;
  logfile.open(outputfile.c_str(), std::ios::out);
  if (logfile.is_open()) {
    std::string outputline;
    outputline = "Opened log: " + outputfile;
    Log(SUCCESS, outputline, "pessum/logging/InitializeLogging");
    LogTimeStamp(true);
    return (true);
  } else {
    return (false);
  }
}

void pessum::logging::Log(LogType type, std::string logstring,
                          std::string logfilelocation) {
  std::string logline =
      InterpretType(type) + logstring + ">>" + logfilelocation;
  if (logfile.is_open() && devmode == false &&
      (type == ERROR || type == WARNING)) {
    logfile << logline << std::endl;
  } else if (logfile.is_open() && devmode == true) {
    logfile << logline << std::endl;
  }
}

void pessum::logging::LogLoc(LogType type, std::string logstring,
                             int logfilelocation, std::string functionname) {
  std::string logline = InterpretType(type) + logstring + ">>" +
                        loglocationbindings[logfilelocation] + functionname;
  if (logfile.is_open() && devmode == false &&
      (type == ERROR || type == WARNING)) {
    logfile << logline << std::endl;
  } else if (logfile.is_open() && devmode == true) {
    logfile << logline << std::endl;
  }
}

std::string pessum::logging::InterpretType(LogType type) {
  std::string logtypeline = "";
  if (type == ERROR) {
    logtypeline = "ERROR>>";
  } else if (type == WARNING) {
    logtypeline = "WARNING>>";
  } else if (type == SUCCESS) {
    logtypeline = "SUCCESS>>";
  } else if (type == DATA) {
    logtypeline = "DATA>>";
  } else if (type == INFORMATION) {
    logtypeline = "INFORMATION>>";
  } else if (type == DEVELOPMENT_CHECK) {
    logtypeline = "DEVCHECK>>";
  } else {
    logtypeline = "LOG TYPE NOT RECOGNIZED";
  }
  return (logtypeline);
}

int pessum::logging::AddLogLocation(std::string loglocationstring) {
  int loglocationindex = loglocationbindings.size();
  loglocationbindings.push_back(loglocationstring);
  return loglocationindex;
}

void pessum::logging::LogTimeStamp(bool date) {
  time_t currenttime;
  time(&currenttime);
  std::string timestring = ctime(&currenttime);
  std::string newtime = "";
  if (date == true) {
    for (unsigned a = 0; a < timestring.size() - 1; a++) {
      newtime = newtime + timestring[a];
    }
  } else {
    for (unsigned a = 11; a < timestring.size() - 6; a++) {
      newtime = newtime + timestring[a];
    }
  }
  Log(INFORMATION, newtime, "TimeStamp");
}

void pessum::logging::TerminateLogging() {
  if (logfile.is_open()) {
    Log(SUCCESS, "Terminated log file", "pessum/logging/TerminateLogging");
    LogTimeStamp(true);
    logfile.close();
  }
  loglocationbindings.clear();
}

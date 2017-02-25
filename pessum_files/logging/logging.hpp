#ifndef PESSUM_LOGGING_HPP
#define PESSUM_LOGGING_HPP
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
namespace pessum {
namespace logging {
extern std::ofstream logoutputfile;
extern std::vector<std::tuple<std::string, int, std::string>>
    loglocationbindings;
extern bool devmode, logtimes;
void InitializeLogging(std::string outputfile, bool recordtime, bool dev);
void TerminateLogging();

int AddLogLocation(std::string locationstring);

void Log(std::string typestr = "", std::string logstr = "",
         std::string locationstr = "", std::string functionstr = "");

void LogTimeStamp(bool date);

std::string GetLocation(int index);
std::string GetLocation(std::string str);
std::string RemoveCaps(std::string str);
std::string GetType(std::string str);
}
}
#endif

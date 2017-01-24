#ifndef _PESSUM_FILES_LOGGING_H_
#define _PESSUM_FILES_LOGGING_H_
#include "pessum_core.h"
#include <fstream>
#include <string>
#include <vector>
namespace pessum {
// logging namespace is used to provide debuging assistance to the
// user. It saves data to a seperate file incase of a crash.
namespace logging {
// Used to define different posible log types
enum LogType { ERROR, WARNING, SUCCESS, DATA, INFORMATION, DEVELOPMENT_CHECK };
extern std::ofstream logfile;
extern std::vector<std::string> loglocationbindings;
extern bool devmode;
// Used to initialize and open logging file for log output
bool InitializeLogging(std::string outputfile = "output.log", bool dev = false);
// Enters the logstring into the output log
void Log(LogType type = DEVELOPMENT_CHECK, std::string logstring = "NULL",
         std::string logfilelocation = "NULL");
void LogLoc(LogType type = DEVELOPMENT_CHECK, std::string logstring = "NULL",
            int logfilelocation = 0, std::string functionname = "NULL");
// Used to determin log type and convert into a string
std::string InterpretType(LogType type);
// Used to add a log location to the vector, making logging shorter
int AddLogLocation(std::string loglocationstring);
// Used to log current time/date
void LogTimeStamp(bool date = false);
// Used to clear loglocationbindigns, and close out the outputfile
void TerminateLogging();
}
}
#endif // !_PESSUM_FILES_LOGGING_H_

#include <string>
#include <fstream>
#include <ctime>
#include "console_logging.h"

namespace pessum {
	namespace consolelogging {
		std::ofstream logfile;
		std::vector<std::string> loglocationbindings;
	}
}

bool pessum::consolelogging::InitializeConsoleLogging(std::string outputfile)
{
	logfile.open(outputfile.c_str(), NULL);
	if (logfile.is_open()) {
		std::string outputline;
		time_t logopentime = time(NULL);
		outputline = "Opened log: " + outputfile + " at: " + std::to_string(logopentime);
		Log(LOG_SUCCESS, outputline, "/Pessum/console_logging.cpp");
		return(true);
	}
	else {
		return(false);
	}
}

void pessum::consolelogging::Log(LogType type, std::string logstring, std::string logfilelocation)
{
	std::string logline = InterpretType(type) + logstring + ">>" + logfilelocation;
	if (logfile.is_open()) {
		logfile << logline << std::endl;
	}
}

void pessum::consolelogging::Log(LogType type, std::string logstring, int logfilelocation)
{
	std::string logline = InterpretType(type) + logstring + ">>" + loglocationbindings[logfilelocation];
	if (logfile.is_open()) {
		logfile << logline << std::endl;
	}
}

std::string pessum::consolelogging::InterpretType(LogType type)
{
	std::string logtypeline = "";
	if (type == LOG_ERROR) {
		logtypeline = "ERROR>>";
	}
	else if (type == LOG_WARNING) {
		logtypeline = "WARNING>>";
	}
	else if (type == LOG_SUCCESS) {
		logtypeline = "SUCCESS>>";
	}
	else if (type == LOG_DATA) {
		logtypeline = "DATA>>";
	}
	else if (type == LOG_DEVELOPMENT_CHECK) {
		logtypeline = "DEVCHECK>>";
	}
	else {
		logtypeline = "LOG TYPE NOT RECOGNIZED";
	}
	return(logtypeline);
}

int pessum::consolelogging::AddLogLocation(std::string loglocationstring)
{
	int loglocationindex = loglocationbindings.size();
	loglocationbindings.push_back(loglocationstring);
	return loglocationindex;
}

void pessum::consolelogging::TerminateConsoleLogging()
{
	if (logfile.is_open()) {
		time_t logclosetime = time(NULL);
		Log(LOG_SUCCESS, "Terminated log file at: " + std::to_string(logclosetime), "/Pessum/console_logging.cpp");
		logfile.close();
	}
	loglocationbindings.clear();
}
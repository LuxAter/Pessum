#ifndef PESSUM_PESSUM_CONSOLE_LOGGING_H_
#define PESSUM_PESSUM_CONSOLE_LOGGING_H_
#include <string>
#include <fstream>
#include <vector>
namespace pessum {
	namespace consolelogging {
		//Used to define different posible log types
		enum LogType
		{
			LOG_ERROR,
			LOG_WARNING,
			LOG_SUCCESS,
			LOG_DATA,
			LOG_DEVELOPMENT_CHECK
		};
		extern std::ofstream logfile;
		extern std::vector<std::string> loglocationbindings;
		//Used to initialize and open logging file for log output
		bool InitializeConsoleLogging(std::string outputfile);
		//Enters the logstring into the output log
		void Log(LogType type, std::string logstring, std::string logfilelocation);
		void Log(LogType type, std::string logstring, int logfilelocation);
		//Used to determin log type and convert into a string
		std::string InterpretType(LogType type);
		//Used to add a log location to the vector, making logging shorter
		int AddLogLocation(std::string loglocationstring);
		//Used to clear loglocationbindigns, and close out the outputfile
		void TerminateConsoleLogging();
	}
}
#endif // !PESSUM_PESSUM_CONSOLE_LOGGING_H_

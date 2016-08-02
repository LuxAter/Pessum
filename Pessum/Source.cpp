#include "Pessum\pessum_core.h";
#include "Pessum\console_logging.h"
int main(int argc, char* argv[]) {
	pessum::consolelogging::InitializeConsoleLogging("console_log_output.log");
	pessum::consolelogging::Log(pessum::consolelogging::LOG_DEVELOPMENT_CHECK, "TEST", "Source.cpp");
	pessum::consolelogging::TerminateConsoleLogging();
	return(0);
}
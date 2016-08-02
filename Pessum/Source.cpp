#include "Pessum\pessum_core.h";
#include "Pessum\logging.h"
int main(int argc, char* argv[]) {
	logging::InitializeConsoleLogging();
	logging::TerminateConsoleLogging();
	return(0);
}
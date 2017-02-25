#include "logging/logging.hpp"
#include "pessum_core.hpp"

void pessum::InitializePessum(bool devmode, bool logtimes) {
  logging::InitializeLogging("output.log", logtimes, devmode);
}

void pessum::TerminatePessum() { logging::TerminateLogging(); }

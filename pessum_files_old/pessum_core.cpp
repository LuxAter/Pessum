#include "logging.h"
#include "lux_reader.h"
#include "parser.h"
#include "pessum_core.h"
#include "rest.h"

void pessum::InitializePessumComponents(bool devmode) {
  logging::InitializeLogging("output.log", devmode);
  luxreader::InitializeLuxReader();
  rest::Initialzierest();
  parser::InitalizeParser();
}

void pessum::TerminatePessumComponents() {
  rest::Terminaterest();
  logging::TerminateLogging();
}

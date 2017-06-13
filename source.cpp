#include <iostream>
#include "pessum.h"

void handle(std::string str) { std::cout << str << "\n"; }

int main(int argc, char const* argv[]) {
  pessum::SetLogHandle(handle);
  pessum::SetLogOption(pessum::TIME_STAMP, true);
  pessum::Log(pessum::ERROR, "ERROR 1", "main");
  pessum::Log(pessum::WARNING, "WARNING 2", "main");
  pessum::Log(pessum::TRACE, "TRACE 3", "main");
  pessum::Log(pessum::DEBUG, "DEBUG 4", "main");
  pessum::Log(pessum::SUCCESS, "SUCCESS 5", "main");
  pessum::Log(pessum::INFO, "INFO 6", "main");
  pessum::Log(pessum::DATA, "DATA 7", "main");
  pessum::SaveLog("out.log");
  return 0;
}

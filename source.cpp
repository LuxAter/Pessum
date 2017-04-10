#include <iostream>
#include "pessum.h"

void handle(std::string str) { std::cout << str << "\n"; }

using namespace pessum::log;

int main(int argc, char const* argv[]) {
  SetLogHandle(handle);
  Log(TRACE, "Test log of everything", "main");
  return 0;
}

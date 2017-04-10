#include <iostream>
#include "pessum.h"

void handle(std::string str) { std::cout << str << "\n"; }

int main(int argc, char const* argv[]) {
  pessum::SetLogHandle(handle);
  pessum::Log(
      pessum::TRACE,
      "Hello arden, %i this is a test to see if I can find why it dident "
      "work at first. Test MSG #%i",
      "main", 1998, 0);
  return 0;
}

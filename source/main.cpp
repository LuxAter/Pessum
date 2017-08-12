#include <iostream>
#include "log.hpp"

int main(int argc, char const* argv[]) {
  pessum::Log(pessum::SUCCESS, "Made pessum logging in header only!", "main");
  pessum::SaveLog("out.log");
}

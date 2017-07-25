#include <iostream>
#include "pessum.hpp"

void handle(std::string str) { std::cout << str << "\n"; }

int main(int argc, char const* argv[]) {
  pessum::SetLogHandle(handle);

  pessum::yaml::Node node;
  node[0]["martin"]["name"] = "Martin D'vloper";
  node[0]["martin"]["job"] = "Devloper";
  node[0]["martin"]["skills"][0] = "python";
  node[0]["martin"]["skills"][1] = "perl";
  node[0]["martin"]["skills"][2] = "pascal";
  node[1]["tabitha"]["name"] = "Tabitha Bitumen";
  node[1]["tabitha"]["job"] = "Developer";
  node[1]["tabitha"]["skills"][0] = "lisp";
  node[1]["tabitha"]["skills"][1] = "fortran";
  node[1]["tabitha"]["skills"][2] = "erlang";

  std::cout << node << std::endl;

  std::cout << "==================\n";

  std::string str = "tabitha.skills.python";
  std::cout << node.find(str) << std::endl;

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

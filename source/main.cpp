#include <iostream>
#include "pessum.hpp"

void handle(std::string str) { std::cout << str << "\n"; }

int main(int argc, char const* argv[]) {
  pessum::SetLogHandle(handle);

  pessum::yaml::Node yaml;
  yaml["name"] = "Martin D'vlopr";
  yaml["job"] = "Developer";
  yaml["skill"] = "Elite";
  yaml["employed"] = true;
  yaml["foods"][0] = "Apple";
  yaml["foods"][1] = "Orange";
  yaml["foods"][2]["Strawberry"]["red"] = 0.5;
  yaml["foods"][2]["Strawberry"]["blue"] = 0;
  yaml["foods"][2]["Strawberry"]["green"] = 0.5;
  yaml["foods"][3] = "Mango";
  yaml["languages"]["perl"] = "Elite";
  yaml["languages"]["python"] = "Elite";
  yaml["languages"]["pascal"] = "Lame";

  pessum::yaml::Node node;

  node = pessum::yaml::LoadFromFile("ex.yaml");

  yaml["languages"]["cpp"] = 90001;
  node["languages"]["cpp"] = 90001;

  yaml["foods"].push_back("Bannana");
  node["foods"].push_back("Bannana");

  std::cout << yaml << std::endl;

  std::cout << "=============================\n";

  std::cout << node << std::endl;

  std::cout << std::endl << node.find("foods.Strawberry") << std::endl;

  // pessum::SetLogOption(pessum::TIME_STAMP, true);
  // pessum::Log(pessum::ERROR, "ERROR 1", "main");
  // pessum::Log(pessum::WARNING, "WARNING 2", "main");
  // pessum::Log(pessum::TRACE, "TRACE 3", "main");
  // pessum::Log(pessum::DEBUG, "DEBUG 4", "main");
  // pessum::Log(pessum::SUCCESS, "SUCCESS 5", "main");
  // pessum::Log(pessum::INFO, "INFO 6", "main");
  // pessum::Log(pessum::DATA, "DATA 7", "main");
  pessum::SaveLog("out.log");
  return 0;
}

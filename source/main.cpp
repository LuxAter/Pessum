#include <iostream>
#include "pessum.hpp"

void handle(std::string str) { std::cout << str << "\n"; }

int main(int argc, char const* argv[]) {
  pessum::SetLogHandle(handle);

  pessum::yaml::Node yaml, yaml2;

  pessum::yaml::Node node;

  node = pessum::yaml::LoadFromFile("ex.yaml");

  yaml = node;

  node("foods.Strawberry.blue") = "Hello";

  std::cout << yaml << std::endl;

  std::cout << "=============================\n";

  std::cout << node << std::endl;

  std::cout << "=============================\n";

  pessum::yaml::Node node2("Hello World!");

  std::cout << node2 << std::endl;

  if (node2 == "Hello World!") {
    std::cout << true;
  } else {
    std::cout << false;
  }
  std::cout << "\n";
  return 0;
}

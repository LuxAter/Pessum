#include "pessum_files/pessum_headers.hpp"
#include <iostream>
int main(int argc, char *argv[]) {
  pessum::InitializePessum(true, true);
  pessum::luxreader::LoadLuxFile("list.lux");
  pessum::TerminatePessum();
  return (1);
}

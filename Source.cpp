#include "pessum_files/pessum_headers.hpp"
#include <iostream>
#include <vector>
int main(int argc, char *argv[]) {
  pessum::InitializePessum(true, true);
  pessum::TerminatePessum();
  return (1);
}

#include "pessum_files/pessum_headers.hpp"
int main(int argc, char *argv[]) {
  pessum::InitializePessum(true, true);
  pessum::TerminatePessum();
  return (1);
}

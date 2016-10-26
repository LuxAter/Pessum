#include "pessum_files/pessum_headers.h"
int main(int argc, char *argv[]) {
  pessum::InitializePessumComponents();
  pessum::TerminatePessumComponents();
  return (1);
}

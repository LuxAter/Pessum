#ifndef _PESSUM_FILES_PESSUM_CORE_H_
#define _PESSUM_FILES_PESSUM_CORE_H_
// pessum namespace is a compleate namespace for the pessum components
namespace pessum {
namespace logging {}
namespace luxreader {}
namespace rest {}
// Runs initialization funcitons for logging, luxreader, and rest
void InitializePessumComponents();
// Runs terminatrion functions for rest, and logging
void TerminatePessumComponents();
}
#endif // !_PESSUM_FILES_PESSUM_CORE_H_
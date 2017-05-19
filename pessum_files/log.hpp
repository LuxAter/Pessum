#ifndef PESSUM_LOG_HPP
#define PESSUM_LOG_HPP
#include <string>
#include <vector>
namespace pessum {
  enum LogType { ERROR, WARNING, TRACE, DEBUG, SUCCESS, INFO, DATA, NONE };
  extern std::vector<std::pair<int, std::string>> global_logs;
  extern void (*log_handle_full)(std::pair<int, std::string>);
  extern void (*log_handle)(std::string);
  void Log(int type = TRACE, std::string msg = "", std::string func = "", ...);
  std::string GetLog(int type);
  std::pair<int, std::string> FGetLog(int type);
  std::string IGetLog(int index);
  std::pair<int, std::string> IFGetLog(int index);
  std::vector<std::string> VGetLog(int start, int end);
  std::vector<std::pair<int, std::string>> VFGetLog(int start, int end);
  void SetLogHandle(void (*handle)(std::pair<int, std::string>));
  void SetLogHandle(void (*handle)(std::string));
  std::string GetTypeStr(int type);
  void SaveLog(std::string file);
}
#endif

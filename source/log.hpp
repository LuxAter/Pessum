#ifndef PESSUM_LOG_HPP
#define PESSUM_LOG_HPP
#include <array>
#include <string>
#include <vector>
namespace pessum {
  enum LogOptions { TIME_STAMP, DATE_STAMP };
  enum LogType { ERROR, WARNING, TRACE, DEBUG, SUCCESS, INFO, DATA, NONE };
  void Log(int type = TRACE, std::string msg = "", std::string func = "", ...);
  int GetLogSize();
  void ClearLogs();
  std::string GetLog(int type);
  std::pair<int, std::string> FGetLog(int type);
  std::string IGetLog(int index);
  std::pair<int, std::string> IFGetLog(int index);
  std::vector<std::string> VGetLog(int start, int end);
  std::vector<std::pair<int, std::string>> VFGetLog(int start, int end);
  void SetLogHandle(void (*handle)(std::pair<int, std::string>));
  void SetLogHandle(void (*handle)(std::string));
  void SetLogOption(int option, int setting);
  std::string GetTypeStr(int type);
  void SaveLog(std::string file);
}
#endif

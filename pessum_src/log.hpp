#ifndef PESSUM_LOGGING_HPP
#define PESSUM_LOGGING_HPP
#include <string>
#include <vector>
//! Core namespace for all pessum methods
namespace pessum {
  //! LogType enum
  /*! Enum of log types for different situations.*/
  enum LogType {
    ERROR /*!< Error log type*/,
    WARNING /*!< Warning log type*/,
    TRACE /*!< Trace log type, for finding position in the program*/,
    DEBUG /*!< Debug log type, for final debuging*/,
    SUCCESS /*!< Success log type*/,
    INFO /*!< Info log type, for program information*/,
    DATA /*!< Data log type, for data output*/,
    NONE /*!< No log type*/
  };
  extern std::vector<std::pair<int, std::string>>
      global_logs; /*!< Vector storing all previously called log outputs*/
  extern void (*log_handle_full)(
      std::pair<int, std::string>);       /*!< Pointer to
                                             function for
                                             handling log
                                             calls with full
                                             log information*/
  extern void (*log_handle)(std::string); /*!< Pointer to funciton for
                                                   handling logs with only
                                                   formated string*/
  //! Log output member
  /*! Function for all logging output. Log entry is saved to global_logs.
    \param type The type of log entry
    \param msg Format string of log entry
    \param func The name of the function creating the log entry
    \sa global_logs, GetLog()
  */
  void Log(int type, std::string msg, std::string func);

  //! Get log entry; full
  /*! Gets last log entry of specified type with full information.
    \param type The type of log entry to find
    \return Pair of log type and formated string of log entry
    \sa GetLog()
  */
  std::pair<int, std::string> FGetLog(int type);

  //! Get log entry
  /*! Gets last log entry of specified type with formated string.
    \param type The type of log entry to find
    \return Formated string of log entery
    \sa FGetLog()
  */
  std::string GetLog(int type);

  //! Get log entry; full index
  /*! Gets last log entry of specified index with full information.
    \param index The log entry index from global_logs
    \return Pair of log type and formated string of log entry
    \sa IGetLog()
  */
  std::pair<int, std::string> IFGetLog(int index);

  //! Get log entry; index
  /*! Gets last log entry of specified index with full information.
    \param index The log entry index from global_logs
    \return Formated string of log entry
    \sa IFGetLog()
  */
  std::string IGetLog(int index);

  //! Get log entry; full vector
  /*! Gets a set of log entries between specified start and end index with
    full information.
    \param start The first index value
    \param end The last index value
    \return vector of pairs of log types and formated strings
    \sa VGetLog()
  */
  std::vector<std::pair<int, std::string>> VFGetLog(int start, int end);

  //! Get log entry; vector
  /*! Gets a set of log entries between specified start and end index with
    formated string.
    \param start The first index value
    \param end The last index value
    \return vector of formated strings
    \sa VFGetLog()
  */
  std::vector<std::string> VGetLog(int start, int end);

  //! Set log handle full
  /*! Sets log_handle_full with specified function pointer
    \param handle Pointer to function with return of void and args of a pair
    of int and string
  \sa log_handle_full*/
  void SetLogHandle(void (*handle)(std::pair<int, std::string>));

  //! Set log handle
  /*! Sets log_handle with specified function pointer
    \param handle Pointer to function with return of void and args of a string
  \sa log_handle_full*/
  void SetLogHandle(void (*handle)(std::string));

  //! Get type string from type int
  /*! Determins the string corisponding to type int
    \param type Type in to convert to string
    \return String corisponding to type int
    \sa LogType
  */
  std::string GetTypeStr(int type);

  //! Saves log entries to file
  /*! Saves the log entries from global_log to specified file path
    \param file Path to file to output to log, defaults to "output.log"
    \sa global_logs
  */
  void SaveLog(std::string file);
}
#endif

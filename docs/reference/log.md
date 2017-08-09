# Logging #

```cpp
#include <pessum/log.hpp>
```

The logging functionality of Pessum is very simple. It permits logs entries to
be added to a set of global log entries, which is handled internaly. These log
entries can then be handled by providing a handle function which is called at
the addition of a log entry, or they can be retreved later through one of the
several log retreval functions. The entire list of log entries can also be
saved to an external file through the save log function.

### Summary ###

| Enumerators               | Descriptions                        |
|---------------------------|-------------------------------------|
| [LogOptions](#LogOptions) | Options used to specify log options |
| [LogType](#LogType)       | Options used to define the type     |

|        | Functions                                                     | Description                          |
|--------|---------------------------------------------------------------|--------------------------------------|
| void   | [Log](#Log)(int type, std::string msg, std::string func, ...) | Enters log entry into system         |
| size_t | [GetLogSize](#GetLogSize)()                                   | Gets length of log entries           |
| void   | [ClearLogs](#ClearLogs)()                                     | Clears all log entries               |
| string | [GetLog](#GetLog)(int type)                                   | Gets last log entry of matching type |

## Enumerators ##

### <a name="LogOptions"></a>LogOptions ###

Options used to specify log option to set in [SetLogOption](#SetLogOption).

| Option     | Value | Note                         |
|------------|-------|------------------------------|
| TIME_STAMP | 0     | Enables time stamps on logs. |
| DATE_STAMP | 1     | Enables date stamps on logs. |

### <a name="LogType"></a>LogType ###

Options used to define the type and importance of the log entry. Must be
provided when [Log](#Log) is called.

| Option  | Value | Node                                  |
|---------|-------|---------------------------------------|
| ERROR   | 0     | Error log type                        |
| WARNING | 1     | Warning log type                      |
| TRACE   | 2     | Trace log type                        |
| DEBUG   | 3     | Debug log type (only for development) |
| SUCCESS | 4     | Success log type                      |
| INFO    | 5     | Information log type                  |
| DATA    | 6     | Data log type                         |
| NONE    | 7     | No log type                           |

## Functions ##

### <a name="Log"></a>Log ###

```cpp
void Log(int type, std::string msg, std::string func, ...)
```
Saves formatted string, log types, and function to global log entries.

 - `type` Sets log type
 - `msg` Log format string
 - `func` Name of function that called the log
 - `...` Additional format arguments


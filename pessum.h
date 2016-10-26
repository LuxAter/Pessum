#ifndef _PESSUM_FILES_PESSUM_CORE_H_
#define _PESSUM_FILES_PESSUM_CORE_H_
#include <fstream>
#include <string>
#include <vector>
// pessum namespace is a compleate namespace for the pessum components
namespace pessum {
// logging namespace is used to provide debuging assistance to the
// user. It saves data to a seperate file incase of a crash.
namespace logging {
// Used to define different posible log types
enum LogType {
  LOG_ERROR,
  LOG_WARNING,
  LOG_SUCCESS,
  LOG_DATA,
  LOG_INFORMATION,
  LOG_DEVELOPMENT_CHECK
};
extern std::ofstream logfile;
extern std::vector<std::string> loglocationbindings;
// Used to initialize and open logging file for log output
bool InitializeLogging(std::string outputfile = "log_output.log");
// Enters the logstring into the output log
void Log(LogType type = LOG_DEVELOPMENT_CHECK, std::string logstring = "NULL",
         std::string logfilelocation = "NULL");
void LogLoc(LogType type = LOG_DEVELOPMENT_CHECK,
            std::string logstring = "NULL", int logfilelocation = 0,
            std::string functionname = "NULL");
// Used to determin log type and convert into a string
std::string InterpretType(LogType type);
// Used to add a log location to the vector, making logging shorter
int AddLogLocation(std::string loglocationstring);
// Used to log current time/date
void LogTimeStamp(bool date = false);
// Used to clear loglocationbindigns, and close out the outputfile
void TerminateLogging();
}
#endif // !_PESSUM_FILES_LOGGING_H_
// luxreader namespace provides support for lux files, and reading the data
// files from lux code to be used in a program.
namespace luxreader {
// Struct for raw lux code loading
struct RawLuxCode {
  std::vector<std::string> luxcodelines;
};
// Structs for lux menu loading
struct List {
  std::string listname;
  std::vector<std::string> listitems;
};
struct Page {
  std::string pagename;
  std::vector<List> pagelists;
};
struct Hierarchy {
  std::string hierarchyname;
  std::vector<Page> mierarchypages;
};
// Structs for lux data loading
struct Variable {
  std::string variablename, variabletype, variabledefinitiontype;
  int intvalue;
  std::vector<int> intvectorvalues;
  double doublevalue;
  std::vector<double> doublevectorvalues;
  std::string stringvalue;
  std::vector<std::string> stringvectorvalues;
};
struct DataFile {
  std::string datafilename;
  std::vector<Variable> datafilevariables;
};
// Defines different types of Lux Code files for the file reader
enum LuxFileType { LUX_DATA, LUX_HIERARCHY, LUX_CODE, LUX_LIST };
// Sets log location for lux reader logging
extern int logloc;

// Sets the logging location code(must be called)
void InitializeLuxReader();

// Loads the data from a lux data file, and returns in a DataFile struct
DataFile LoadLuxDataFile(std::string filedirectory);
// Loads the data from a lux hierarchy file, and returns in a Hierarchy struct
Hierarchy LoadLuxHierarchyFile(std::string filedirectory);
// Loads the data from a lux list file, and returns in a vector of strings
std::vector<std::string> LoadLuxListFile(std::string filedirectory);

// Takes a DataFile structure, and converts it to RawLuxCode, to output
void SaveLuxDataFile(std::string filedirectory, DataFile ouputdata);

// Loads the raw lux code data from specified file
RawLuxCode GetRawFileData(LuxFileType filetype, std::string filedirectory);
// Saves a raw lux code data to specifed file
void OuputRawFileData(LuxFileType filetype, std::string filedirectory,
                      RawLuxCode rawoutputcode);
}
// rest namespace allows access to urls and internet
// api through the use of return json files
namespace rest {
// Struct for variables in json files
struct Variable {
  std::string variablename;
  std::vector<Variable> subvariables;
  std::string stringvalue;
  int intvalue;
  double doublevalue;
};
// Struct for json file variables
struct JsonFile {
  std::vector<Variable> filevariables;
};
// Log location integer index
extern int logloc;
// Int index to identify level of json file branches
extern unsigned int index;
// Vector of loaded json files
extern std::vector<JsonFile> loadedjsonfiles;
// Sets log location for rest logging
void Initialzierest();
// Clears loaded json files, freeing up memory
void Terminaterest();

// Runs specified python script with script arguments from vector
void RunScript(std::vector<std::string> scriptargs);
// Reads script output file, and creates a JsonFile from the raw file
void InterpretJson(std::string scriptoutputfiledirectory);
// Reads contents of a variable, and returns a Variable structure from raw
// variable string
Variable InterpretVariable(std::string variablename, std::string rawvariable);
// Access json file from loaded json file vector
JsonFile GetJsonFile(std::string filename);

// Returns sub variable searched from variable
Variable LocateVariable(std::string variablename, Variable searchvariable);
// Returns sub variable searched from json file
Variable GetVariable(std::string variablename, std::string jsonfilename);
// Returns int value searched from json file
int GetIntVariable(std::string variablename, std::string jsonfilename);
// Returns double value searched from json file
double GetDoubleVariable(std::string variablename, std::string jsonfilename);
// Returns string value searched from json file
std::string GetStringVariable(std::string variablename,
                              std::string jsonfilename);
}
// Runs initialization funcitons for logging, luxreader, and rest
void InitializePessumComponents();
// Runs terminatrion functions for rest, and logging
void TerminatePessumComponents();
}
#endif // !_PESSUM_FILES_PESSUM_CORE_H_

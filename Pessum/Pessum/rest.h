#ifndef _PESSUM_REST_H_
#define _PESSUM_REST_H_
#include <string>
#include <vector>

namespace rest {
	struct Variable
	{
		std::string variablename;
		std::vector<Variable> subvariables;
		std::string stringvalue;
		int intvalue;
		double doublevalue;
	};
	struct JsonFile
	{
		std::vector<Variable> filevariables;
	};
	extern int logloc;
	extern unsigned int index;
	extern std::vector<JsonFile> loadedjsonfiles;
	void Initialzierest();

	void RunScript(std::vector<std::string> scriptargs);
	void InterpretJson(std::string scriptoutputfiledirectory);
	Variable InterpretVariable(std::string variablename, std::string rawvariable);
	JsonFile GetJsonFile(std::string filename);

	Variable LocateVariable(std::string variablename, Variable searchvariable);
	Variable GetVariable(std::string variablename, std::string jsonfilename);
	int GetIntVariable(std::string variablename, std::string jsonfilename);
	double GetDoubleVariable(std::string variablename, std::string jsonfilename);
	std::string GetStringVariable(std::string variablename, std::string jsonfilename);
}
#endif // !_PESSUM_REST_H_

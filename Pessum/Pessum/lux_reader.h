#ifndef _PESSUM_LUX_READER_H_
#define _PESSUM_LUX_READER_H_
#include <string>
#include <vector>

namespace luxreader {
	//Struct for raw lux code loading
	struct RawLuxCode
	{
		std::vector<std::string> luxcodelines;
	};
	//Structs for lux menu loading
	struct List
	{
		std::string listname;
		std::vector<std::string> listitems;
	};
	struct Page
	{
		std::string pagename;
		std::vector<List> pagelists;
	};
	struct Hierarchy
	{
		std::string hierarchyname;
		std::vector<Page> mierarchypages;
	};
	//Structs for lux data loading
	struct Variable
	{
		std::string variablename, variabletype, variabledefinitiontype;
		int intvalue;
		std::vector<int> intvectorvalues;
		double doublevalue;
		std::vector<double> doublevectorvalues;
		std::string stringvalue;
		std::vector<std::string> stringvectorvalues;
	};
	struct DataFile
	{
		std::string datafilename;
		std::vector<Variable> datafilevariables;
	};

	enum LuxFileType
	{
		LUX_DATA,
		LUX_HIERARCHY,
		LUX_CODE,
		LUX_LIST
	};
	extern int logloc;

	void InitializeLuxReader();

	DataFile LoadLuxDataFile(std::string filedirectory);
	Hierarchy LoadLuxHierarchyFile(std::string filedirectory);

	void SaveLuxDataFile(std::string filedirectory, DataFile ouputdata);

	RawLuxCode GetRawFileData(LuxFileType filetype, std::string filedirectory);
	void OuputRawFileData(LuxFileType filetype, std::string filedirectory, RawLuxCode rawoutputcode);
}
#endif // !_PESSUM_LUX_READER_H_
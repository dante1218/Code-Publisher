/////////////////////////////////////////////////////////////////////////
// Loader.cpp   - given folder path, store all valid file in vector    //
// ver 1.0                                                             //
// Language:      C++, Visual Studio 2017                              //
// Application:   Project3, CSE687 - OOD Spring 2019                   //
// Author:        Yishi Lu, Syracuse University, EECS                  //
//                ylu154@syr.edu                                       //
/////////////////////////////////////////////////////////////////////////

#include "Loader.h"
#include "../FawcettPackage/FileSystem/FileSystem.h"

//----< given a path, search all .h and .cpp file in the path, and store their name in vector fileList >---------------------------------------
void Loader::searchFile(std::vector<std::string> &fileList, std::string filePath)
{
	std::cout << "  Searching all .h and .cpp files in the given directory:";
	FileSystem::DirExplorerN dirExp(filePath);
	dirExp.addPattern("*.h");
	dirExp.addPattern("*.cpp");
	dirExp.recurse(true);
	dirExp.search(fileList);
	dirExp.showStats();
}

//----< given a pattern and list of file, retrun a list of files which are matched to the pattern>-----
int Loader::filterFile(std::vector<std::string> &fileList, std::vector<std::string> &filenameList, const std::string pattern)
{
	int coutValidFile = 0;
	std::vector<std::string> matchedFile;
	RegularExp reg;

	if (!reg.checkPattern(pattern)) return -999999;

	log("Select file by Regular Expression " + pattern + ", selected file is following:");

	for (auto f : fileList)
	{
		std::string filename = FileSystem::Path::getName(f);

		if (reg.matchPattern(filename, pattern))
		{
			matchedFile.push_back(f);
			filenameList.push_back(filename);
			std::cout << "  -- " << f << std::endl;
			coutValidFile++;
		}
	}

	fileList = matchedFile;

	return coutValidFile;
}


#ifdef TEST_LOADER
int main()
{
	std::cout << "\n  Testing Display";
	std::cout << "\n ====================================\n\n";

	Loader find;

	std::vector<std::string> testList;
	std::vector<std::string> testFileNameList;

	std::cout << "\n  Test function searchFile():\n";
	find.searchFile(testList, "..\\FawcettPackage");

	std::cout << "\n  Test function filterFile():\n";
	find.filterFile(testList, testFileNameList, "[A-E].*");
}
#endif // TEST_LOADER


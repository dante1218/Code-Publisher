
///////////////////////////////////////////////////////////////////////
// Analysis.cpp  - parse and analyse input file                      //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Project2, CSE687 - OOD Spring 2019                   //
// Author:      Yishi Lu, Syracuse University, EECS                  //
//              ylu154@syr.edu                                       //
///////////////////////////////////////////////////////////////////////

#include "Analysis.h"
#include "../FawcettPackage/Parser/ConfigureParser.h"
#include "../FawcettPackage/FileSystem/FileSystem.h"

//----< reset value of all private data >----------------------------------------------
void Analysis::reset(bool test)
{
	includedeTagTable.clear();
	classFunctionTagTable.clear();
	commentTagTable.clear();
	commentStartLine = -1, commentEndLine = -1;
	if (test) {
		std::cout << "  size of includedeTagTable: " << includedeTagTable.size() << std::endl;
		std::cout << "  size of classFunctionTagTable: " << classFunctionTagTable.size() << std::endl;
		std::cout << "  size of commentTagTable: " << commentTagTable.size() << std::endl;
		std::cout << "  comment start line: " << commentStartLine << "\n  comment end Line: " << commentEndLine << std::endl;
	}
}

//----< search includeTagTable by given line number >----------------------------------------------
std::string Analysis::searchIncludeTagTable(int lineNum)
{
	if (includedeTagTable.find(lineNum) != includedeTagTable.end())
	{
		std::string result = includedeTagTable.find(lineNum)->second;
		includedeTagTable.erase(lineNum);
		return result;
	}
	return "";
}

//----< search classFunctionTagTable by given line number >----------------------------------------------
std::string Analysis::searchClassFunctionTagTable(int lineNum)
{
	if (classFunctionTagTable.find(lineNum) != classFunctionTagTable.end())
	{
		std::string result = classFunctionTagTable.find(lineNum)->second;
		classFunctionTagTable.erase(lineNum);
		return result;
	}
	return "";
}

//----< search commentTagTable by given line number >----------------------------------------------
std::string Analysis::searchCommentTagTable(int lineNum)
{
	if (commentTagTable.find(lineNum) != commentTagTable.end())
	{
		std::string result = commentTagTable.find(lineNum)->second;
		commentTagTable.erase(lineNum);
		return result;
	}
	return "";
}

//----< parse and analyse input file >----------------------------------------------
void Analysis::analysisFile(std::string path, std::string filename, std::vector<std::string> filenameList)
{
	//log("-- Searching Class and Function");
	findClassFunctionTag(filename, path);
	//log("-- Searching Comment\n");
	findCommentTag(filename, path);
	//log("-- Searching Include Dependency\n");
	findIncludeTag(filename, path, filenameList);
}

//----< find #include tag in the file >----------------------------------------------
void Analysis::findIncludeTag(std::string fileName, std::string path, const std::vector<std::string> fileList)
{
	std::string fileLocation = path + "\\" + fileName;

	Lexer::Toker toker;
	toker.doReturnComments(false);
	toker.open(fileLocation);

	while (!toker.isDone())
	{
		if (toker.getTok() == "#")
		{
			if (toker.getTok() == "include")
			{
				std::string nextInclude = toker.getTok();
				processIncludeTag(nextInclude, toker.lineCount(), fileList);
			}
		}
	}
	toker.close();
}

//----< process #include tag in the file >----------------------------------------------
void Analysis::processIncludeTag(std::string input, int currentLine, const std::vector<std::string> fileList)
{
	std::string link = "";

	int start = input.find_first_of('"');
	int end = input.find_last_of('"');
	if (start >= 0 && end > start)
	{
		link = input.substr(start + 1, end - start - 1);
		link = FileSystem::Path::getName(link);
		if (std::find(fileList.begin(), fileList.end(), link) != fileList.end())
		{
			includedeTagTable.insert(std::make_pair(currentLine, "include#" + link));
			//log("Find valid #include tag (line " + std::to_string(currentLine) + "): " + link + ", dependency is recorded.");
		}
		//else log("Find #include tag " + link + ", but the corresponding file is not in the processing file list (the file is not to be converted to HTML). So not make dependency.");
	}
}

//----< find and process class/function tag in the file >----------------------------------------------
void Analysis::findClassFunctionTag(std::string fileName, std::string path)
{
	std::string fileLocation = path + "\\" + fileName;

	CodeAnalysis::ConfigParseForCodeAnal configure;
	CodeAnalysis::Parser* pParser = configure.Build();

	configure.Attach(fileLocation);

	while (pParser->next())
		pParser->parse();
	std::cout << "\n";

	CodeAnalysis::Repository* pRepo = CodeAnalysis::Repository::getInstance();
	CodeAnalysis::ASTNode* pGlobalScope = pRepo->getGlobalScope();
	myTreeWalk(pGlobalScope, classFunctionTagTable);
}

//----< find and process comment tag in the file >----------------------------------------------
void Analysis::findCommentTag(std::string fileName, std::string path)
{
	int starLine = -1, endLine = -1;
	std::string fileLocation = path + "\\" + fileName;

	Lexer::Toker toker;
	toker.doReturnComments(true);
	toker.open(fileLocation);

	while (!toker.isDone())
	{
		int count = 0;
		std::string tok = toker.getTok();
		if (toker.isSingleLineComment(tok)) 
		{
			commentTagTable.insert(std::make_pair(toker.lineCount(), "singleLineComment"));
		}
		else if (toker.isMultipleLineComment(tok)) 
		{
			for (char& c : tok) if (c == '\n') count++;
			if(count == 0) commentTagTable.insert(std::make_pair(toker.lineCount(), "oneLineComment"));
			else {
				commentTagTable.insert(std::make_pair(toker.lineCount() - count, "commentStart"));
				commentTagTable.insert(std::make_pair(toker.lineCount(), "commentEnd"));
			}
		}
	}
	toker.close();
}



#ifdef TEST_ANALYSIS
int main()
{
	std::cout << "\n  Testing Analysis";
	std::cout << "\n ====================================\n\n";

	Analysis a;

	std::vector<std::string> fileList;
	fileList.push_back("Analysis.h");
	fileList.push_back("Analysis.cpp");

	std::cout << "  --Test function findIncludeTag():\n";
	a.findIncludeTag("Analysis.cpp", "..\\Analysis", fileList);

	std::cout << "\n\n  --Test function processIncludeTag():\n";
	a.processIncludeTag("#include \"Analysis.h\"", 10, fileList);
	a.processIncludeTag("#include \"test.cpp\"", 10, fileList);

	std::cout << "\n\n  --Test function findClassFunctionTag():\n";
	a.findClassFunctionTag("Analysis.cpp", "..\\Analysis");

	std::cout << "\n\n  --Test function findCommentTag():\n";
	a.findCommentTag("Analysis.cpp", "..\\Analysis");

	std::cout << "\n\n --Test function searchIndlucdeTagTable():\n";
	std::string test = a.searchIncludeTagTable(10);
	if (test != "") std::cout << "  Find value by key 10 in the table, value: " << test << std::endl;
	else std::cout << "  Invalid key.\n";

	std::cout << "\n\n  --Test function searchCommentTagTable():\n";
	test = a.searchCommentTagTable(2);
	if (test != "") std::cout << "  Find value by key 2 in the table, value: " << test << std::endl;
	else std::cout << "  Invalid key.\n";

	std::cout << "\n\n  --Test function classFunctionTagTable():\n";
	test = a.searchClassFunctionTagTable(17);
	if (test != "") std::cout << "  Find value by key 17 in the table, value: " << test << std::endl;
	else std::cout << "  Invalid key.\n";

	std::cout << "\n\n  --Test function reset():\n";
	a.reset(true);
}

#endif // TEST_ANALYSIS


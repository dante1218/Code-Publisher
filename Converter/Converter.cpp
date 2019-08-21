//////////////////////////////////////////////////////////////////////////
// Converter.cpp - converter input file to valid html file              //
// ver 1.0                                                              //
// Language:       C++, Visual Studio 2017                              //
// Application:    Project3, CSE687 - OOD Spring 2019                   //
// Author:         Yishi Lu, Syracuse University, EECS                  //
//                 ylu154@syr.edu                                       //
//////////////////////////////////////////////////////////////////////////

#include "Converter.h"
#include "../FawcettPackage/FileSystem/FileSystem.h"

//----< check if the file is opened or not >----------------------------------------------
bool Converter::checkIfstream(std::ifstream &in, std::string fileName)
{
	if (!in.good()) {
		log("ERROR: " + fileName + " cannot be opened. \n");
		return false;
	}
	return true;
}

//----< check if the file is opened or not >----------------------------------------------
bool Converter::checkOfstream(std::ofstream &out, std::string fileName)
{
	if (!out.good()) {
		log("ERROR: " + fileName + " cannot be opened. \n");
		return false;
	}
	return true;
}

//----< convert "<" and ">" to special token >----------------------------------------------
std::string Converter::convertSpeicalTag(std::string line)
{
	int position;
	std::string left = "<", right = ">";

	while ((position = line.find(left)) != std::string::npos)
		line.replace(position, left.length(), "&lt;");
	while ((position = line.find(right)) != std::string::npos)
		line.replace(position, right.length(), "&gt;");
	return line;
}

//----< call corresponding object (dependencies and display) to insert dependency link and wrapping div >----------------------------------------------
void Converter::processInputFile(std::ofstream &out, std::ifstream &in, Analysis anal)
{
	std::string nextLine = "", type = "";
	int countLine = 1;

	while (getline(in, nextLine)) {
		nextLine = convertSpeicalTag(nextLine);
		type = anal.searchCommentTagTable(countLine);
		if (type != "") {
			nextLine = display.addCommentDiv(type, nextLine);
			type = "";
		}
		type = anal.searchIncludeTagTable(countLine);
		if (type != "") {
			nextLine = dependency.addDependenciesLink(type, nextLine);
			type = "";
		}
		type = anal.searchClassFunctionTagTable(countLine);
		if (type != "") {
			nextLine = display.addClassFunctionDiv(type, nextLine);
			type = "";
		}
		out << nextLine+"\n";
		countLine++;
	}
}

//----< convert input file to valid HTML file >----------------------------------------------
void Converter::makeHTML(std::string fileName, std::string folder, std::string path, Analysis anal)
{
	//log("Starting convert input file to HTML and convert '<' and '>' to '&lt;' and '&gt;' by Converter Package\n");
	std::ifstream inputFile(path + "\\" + fileName);
	if (!checkIfstream(inputFile, fileName)) return;
	fileName = FileSystem::Path::getName(fileName);

	std::ifstream htmlHeader("..\\htmlHeaderTemplate");
	if (!checkIfstream(htmlHeader, "htmlHeaderTemplate")) return;
	
	std::ifstream htmlTail("..\\htmlTailTemplate");
	if (!checkIfstream(htmlTail, "htmlTailTemplate")) return;
	
	std::ofstream convertingFile("..\\" + folder + "\\" + fileName + ".html");
	if (!checkOfstream(convertingFile, fileName + ".html")) return;
	
	std::string nextLine = "";
	while (getline(htmlHeader, nextLine)) convertingFile << nextLine + "\n";
	
	convertingFile << "\n<h3>" + fileName + "</h3>\n";
	convertingFile << "<pre>\n";
	processInputFile(convertingFile, inputFile, anal);
	
	convertingFile << "\n  </pre>\n";
	while (getline(htmlTail, nextLine)) convertingFile << nextLine + "\n";

	inputFile.close();
	htmlHeader.close();
	htmlTail.close();
	convertingFile.close();
}

#ifdef TEST_CONVERTER

int main()
{
	std::cout << "\n  Testing Converter";
	std::cout << "\n ====================================\n\n";

	Converter con;

	std::cout << "  --Test function convertSpeicalTag():\n";
	std::string input = "<> test <<<<< test >>>>> test <><><<>>";
	std::cout << "Input line: " << input << ", Output line: " << con.convertSpeicalTag(input) << std::endl;

	std::cout << "\n\n  --Test function makeHTML() and processInputFile():\n";
	Analysis an;
	std::vector<std::string> fileList;
	fileList.push_back("Converter.h");
	fileList.push_back("Converter.cpp");
	an.analysisFile("..\\Converter", "Converter.cpp", fileList);
	con.makeHTML("Converter.cpp", "test", "..\\Converter", an);
	an.reset();
	an.analysisFile("..\\Converter", "Converter.h", fileList);
	con.makeHTML("Converter.h", "test", "..\\Converter", an);
}

#endif // TESS_CONVERTER


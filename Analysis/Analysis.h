#pragma once

///////////////////////////////////////////////////////////////////////
// Analysis.h  - parse and analyse input file                        //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Project2, CSE687 - OOD Spring 2019                   //
// Author:      Yishi Lu, Syracuse University, EECS                  //
//              ylu154@syr.edu                                       //
///////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one class: Analysis.
 * Its purpose is to parse and analyse content of inputfile
 * It is implemented using ConfigureParser.h
 * We use ConfigureParser.h to parse the input file. We mainly focus on 
 * the comment, #include, and class and function in the file
 * once we found them, their type, start line, and end line will
 * be recorded on corresponding table (unordered_map)
 *
 * This package provides functions:
 * findIncludeTag()					find #include tag in the input file
 * processIncludeTag()				once #include is found, process it
 * findCommentTag()					find comment in the input file
 * findClassFunctionTag()			find class and function in the input file
 * analysisFile()					starting parse and analyse input file
 * searchIndlucdeTagTable()			search result in the indlucdeTagTable
 * searchClassFunctionTagTable()	search result in the classFunctionTagTable
 * searchCommentTagTable()			search result in the commentTagTable
 * reset()							reset all private data
 * log(str)							print message to console
 *
 * Required Files:
 * ---------------
 * Analysis.h, Analysis.cpp
 * ConfigureParser.h, ConfigureParser.cpp
 * FileSystem.h, FileSystem.cpp
 *
 * Build Process:
 * --------------
 * devenv Project2.sln /ReBuild
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 05 March 2019
 * - first release
 */

#include <iostream>
#include <string>
#include <vector>
#include <iterator> 
#include <unordered_map> 

class Analysis
{
	private:
		std::unordered_map<int, std::string> includedeTagTable;

		std::unordered_map<int, std::string> classFunctionTagTable;

		std::unordered_map<int, std::string> commentTagTable;

		int commentStartLine = -1, commentEndLine = -1;

	public:
		void findIncludeTag(std::string fileName, std::string path, const std::vector<std::string> fileList);

		void processIncludeTag(std::string input, int currentLine, const std::vector<std::string> fileList);

		void findCommentTag(std::string fileName, std::string path);

		void findClassFunctionTag(std::string fileName, std::string path);

		void analysisFile(std::string path, std::string filename, std::vector<std::string> filenameList);

		std::string searchIncludeTagTable(int lineNum);

		std::string searchClassFunctionTagTable(int lineNum);

		std::string searchCommentTagTable(int lineNum);

		void reset(bool test = false);

		void log(std::string msg);
};

//----< print message to console >----------------------------------------------
inline void Analysis::log(std::string msg)
{
	std::cout << "  " + msg + "  \n";
}


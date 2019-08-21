#pragma once

/////////////////////////////////////////////////////////////////////////
// Converter.h  - converter input file to valid html file              //
// ver 1.0                                                             //
// Language:      C++, Visual Studio 2017                              //
// Application:   Project3, CSE687 - OOD Spring 2019                   //
// Author:        Yishi Lu, Syracuse University, EECS                  //
//                ylu154@syr.edu                                       //
/////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one class: Converter.
 * Its purpose is to convert input file to a valid html file, the
 * converted file will be stored at another file with name fileName.html.
 * It is implemented using package Dependencies, Display and Analysis:
 * Package Dependencies is used to insert dependency link to output file
 * Package Display is used to insert wrapping <div> to output file
 * Package Analysis stores analysied information about input file, and 
 * we need to retrive those information to insert any link and <div>
 *
 * This package provides functions:
 * makeHTML()                               convert input file to HTML file
 * convertSpeicalTag(str, str, str)			convert "<" or ">" to special token
 * checkIfstream()							check file is opened or not
 * checkOfstream()							check file is opened or not
 * processInputFile()						process input file to produce output file
 * log(str)									print message to console
 *
 *
 * Required Files:
 * ---------------
 * Converter.h, Converter.cpp,
 * Dependencies.h, Dependencies.cpp
 * Display.h, Display.cpp,
 * Analysis.h, Analysis.cpp
 * FileSystem.h, FileSystem.cpp
 *
 * Build Process:
 * --------------
 * devenv Project3.sln /ReBuild
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 05 March 2019
 * - first release
 */

#include <iostream>
#include <fstream>
#include <string>
#include "../Dependencies/Dependencies.h"
#include "../Display/Display.h"
#include "../Analysis/Analysis.h"

class Converter 
{
	private:
		Display display;
		Dependencies dependency;
	public:
		std::string convertSpeicalTag(std::string line);

		void makeHTML(std::string filename, std::string folder, std::string path, Analysis anal);

		bool checkIfstream(std::ifstream &in, std::string fileName);

		bool checkOfstream(std::ofstream &out, std::string fileName);

		void processInputFile(std::ofstream &convertingFile, std::ifstream &inputFile, Analysis anal);

		void log(std::string msg);
};

//----< print message to console >----------------------------------------------
inline void Converter::log(std::string msg)
{
	std::cout << "  " + msg + "  \n";
}




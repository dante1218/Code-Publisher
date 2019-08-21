#pragma once

////////////////////////////////////////////////////////////////////////
// CodePublisher.cpp - accept file path and pattern from user, and    //
//                     then find and convert valid file to a valid    //
//                     html file and insert dependency link and       //
//                     wrapping div                                   //
// ver 1.0                                                            //
// Language:     C++, Visual Studio 2017                              //
// Application:  Project3, CSE687 - OOD Spring 2019                   //
// Author:       Yishi Lu, Syracuse University, EECS                  //
//               ylu154@syr.edu                                       //
////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one class: CodePublisher.
 * The class inherited from CodePubliserInterface, and implement all methods 
 * which are defined in the interface
 * Its purpose is to accept path and pattern from user, then search
 * on the path and convert valid file (match to the pattern) to valid html
 * file. Moreover, also insert dependency link and wrapping tag to the html file
 * It is implemented using Loader.h, Converter.h, and Analysis.h:
 * Loader.h, find all .h and .cpp file in the given path, then using the pattern
 * to select valid files, and storing those file in vector
 * Analysis.h, parse and analysis the input file, find positon of class, function,
 * include, and comment, and store then in different maps
 * Converter.h, convert those found files to valid html file, preappend HTML header
 * template, postappend HTML tail template, and replace special character. It will
 * also invlove Display and Dependencies package to insert dependency link and
 * wrapping dive to the HTML file
 *
 * This package provides functions:
 * CodePublisher()					constrcutor, accept two string, one for path, one for pattern
 * acceptInput()					function used to set path and pattern
 * createFolder(str)				create a folder in project tree for storing converted files
 * findValidFile()					find all valid files
 * converterFile()					convert file to valid HTML file
 * showProcessedFile();             print input file content on console, and open the file by application
 * log(str)							print message to console
 *
 * Required Files:
 * ---------------
 * CodePublisherInterface.h, CodePublisherInterface.cpp
 * CodePublisher.h, CodePublisher.cpp
 * Analysis.h, Analysis.cpp
 * Converter.h, Converter.cpp
 * Loader.h, Loader.cpp
 * Show.h, Show.cpp
 *
 * Build Process:
 * --------------
 * devenv Project3.sln /ReBuild
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 08 April 2019
 * - first release
 */

#include "../Converter/Converter.h"
#include "../Show/Show.h"
#include "../Loader/Loader.h"
#include "../CodePublisherInterface/CodePublisherInterface.h"

class CodePublisher: public CodePublisherInterface {
private:
	Loader find;
	Converter conv;
	Analysis analy;
	Show sh;
	std::vector<std::string> filePath;
	std::vector<std::string> filenameList;
	std::string path;
	std::string pattern;
	std::string browserLocation;
	std::string storingFolder;
public:
	CodePublisher(std::string input_path, std::string input_pattern);
	void acceptInput(std::string input_path, std::string input_pattern);
	void createFolder(std::string folderName);
	bool findValidFile();
	void converterFile();
	void showProcessedFile(std::string filename);
	void log(std::string msg);
};

//----< print message to console >----------------------------------------------
inline void CodePublisher::log(std::string msg)
{
	std::cout << "  " + msg + "  \n";
}




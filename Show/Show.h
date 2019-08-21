#pragma once

///////////////////////////////////////////////////////////////////////
// Show.h - show a file in console or browser                        //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Project3, CSE687 - OOD Spring 2019                   //
// Author:      Yishi Lu, Syracuse University, EECS                  //
//              ylu154@syr.edu                                       //
///////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one class: Show.
 * Its purpose is to show content of a file in given application.
 * FileSystem.h, getFullFileSpec() is called to get full path of target file,
 * Process.h, process object is created to show content of file by given 
 * application.
 *
 * This package provides functions:
 * showHTML()					    open converted file by given application
 * demoConvertion()                 print input file to console
 * checkIfstream()					check file is opened or not
 * log(str)							print message to console
 *
 * Required Files:
 * ---------------
 * Show.h, Show.cpp
 * Process.h, Process.cpp
 * FileSystem.h FileSystem.cpp
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

#include <fstream>
#include <iostream>
#include <string>

class Show
{
public:
	void showHTML(const std::string file, std::string browserLocation);

	void demoConvertion(std::string file);

	bool checkIfstream(std::ifstream &in, std::string fileName);

	void log(std::string msg);
};

//----< print message to console >----------------------------------------------
inline void Show::log(std::string msg)
{
	std::cout << "  " + msg + "  \n";
}
#pragma once

//////////////////////////////////////////////////////////////////////////////
// Dependency.h  - insert dependency link on #inclde tag of .h/.cpp file    //
// ver 1.0                                                                  //
// Language:    C++, Visual Studio 2017                                     //
// Application: Project3, CSE687 - OOD Spring 2019                          //
// Author:      Yishi Lu, Syracuse University, EECS                         //
//              ylu154@syr.edu                                              //
//////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one class: Dependency.
 * Its purpose is to add dependency link <a href="..."></a> 
 * to #include tag in .h/.cppc file.
 * 
 *
 * This package provides functions:
 * addDependenciesLink()	        given type and next line, add corresponding dependency link to the line
 * log(str)							print message to console
 *
 * Required Files:
 * ---------------
 * Dependency.h, Dependency.cpp
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
#include <string>

class Dependencies 
{
	public:
		std::string addDependenciesLink(std::string type, std::string nextLine);

		void log(std::string msg);
};

//----< print message to console >----------------------------------------------
inline void Dependencies::log(std::string msg)
{
	std::cout << "  " + msg + "  \n";
}



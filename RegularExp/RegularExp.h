#pragma once

/////////////////////////////////////////////////////////////////////////
// RegularExp.h - check input string is match to given pattern         //
// ver 1.0                                                             //
// Language:      C++, Visual Studio 2017                              //
// Application:   Project3, CSE687 - OOD Spring 2019                   //
// Author:        Yishi Lu, Syracuse University, EECS                  //
//                ylu154@syr.edu                                       //
/////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one class: RegularExp.
 * Its purpose is to check if input string is match to given pattern.
 * It is implemented using C++11 regex class:
 * Creating a regex object by given pattern, then call function to check
 * if the given input string is match to the pattern
 *
 * This package provides functions:
 * matchPattern(str, str)		check string match to pattern
 * checkPattern(str)            check the pattern is valid regular expression
 * log(str)						print message to console
 *
 * Required Files:
 * ---------------
 * RegularExp.h, RegularExp.cpp
 *
 * Build Process:
 * --------------
 * devenv Project3.sln /ReBuild
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 05 Feb 2019
 * - first release
 */


#include <iostream>
#include <regex>

class RegularExp 
{
	public:
		bool matchPattern(std::string target, std::string pattern);

		bool checkPattern(std::string pattern);

		void log(std::string msg);
};

//----< print message to console >----------------------------------------------
inline void RegularExp::log(std::string msg)
{
	std::cout << "  " + msg + "  \n";
}



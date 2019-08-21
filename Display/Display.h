#pragma once

///////////////////////////////////////////////////////////////////////
// Display.h  - insert <div> to wrapping comment, function and class //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Project3, CSE687 - OOD Spring 2019                   //
// Author:      Yishi Lu, Syracuse University, EECS                  //
//              ylu154@syr.edu                                       //
///////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one class: Display.
 * Its purpose is to insert <div> to every comment, class and function. 
 * so when user click class button, all class will be hide; click 
 * on function button, function will be hide; click on comment, Comment 
 * blocks at the begining of each source code file will be hide
 *
 * This package provides functions:
 * addClassFunctionDiv()			add <div> to a class or funciton
 * addCommentDiv()					add <div> to comment
 *
 * Required Files:
 * ---------------
 * Display.h, Display.cpp
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
#include <vector>


class Display
{
	public:
		std::string addClassFunctionDiv(std::string type, std::string nextLine);

		std::string addCommentDiv(std::string type, std::string nextLine);
};





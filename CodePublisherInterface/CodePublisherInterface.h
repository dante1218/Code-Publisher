#pragma once

/////////////////////////////////////////////////////////////////////////////////
// CodePublisherInterface.cpp - an abtract interface which is used to define   //
//                              any function for CodePublisher. The detail     //
//                              implementation of all function will be defined //
//                              in derived class CodePublisher                 //
// ver 1.0                                                                     //
// Language:            C++, Visual Studio 2017                                //
// Application:         Project3, CSE687 - OOD Spring 2019                     //
// Author:              Yishi Lu, Syracuse University, EECS                    //
//                      ylu154@syr.edu                                         //
/////////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * An abstract interface which provide sereval pure virutal function
 * those functions should be implemented by derived class 
 *
 * This package provides following pure virtual functions:
 * acceptInput()					
 * createFolder(str)				
 * findValidFile()					
 * converterFile()					
 * showProcessedFile();             
 *
 * Required Files:
 * ---------------
 * CodePublisherInterface.h, CodePublisherInterface.cpp
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

//#ifdef IN_DLL
//#define DLL_DECL __declspec(dllexport)
//#else
//#define DLL_DECL __declspec(dllimport)
//#endif

#include <string>

class CodePublisherInterface
{
	public:
		virtual void createFolder(std::string folderName) = 0;
		virtual void acceptInput(std::string input_path, std::string input_pattern) = 0;
		virtual bool findValidFile() = 0;
		virtual void converterFile() = 0;
		virtual void showProcessedFile(std::string filename) = 0;
		virtual void log(std::string msg) = 0;
		virtual ~CodePublisherInterface() {}
};

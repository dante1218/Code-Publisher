#pragma once

/////////////////////////////////////////////////////////////////////////
// Loader.h     - given folder path, store all valid file in vector    //
// ver 1.0                                                             //
// Language:      C++, Visual Studio 2017                              //
// Application:   Project3, CSE687 - OOD Spring 2019                   //
// Author:        Yishi Lu, Syracuse University, EECS                  //
//                ylu154@syr.edu                                       //
/////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package contains one class: Loader.
 * Its purpose is to store all valid file in list by given path and pattern
 * It is implemented using DirExplorerN.h and RegularExp.h:
 * DirExplorerN.h, a DirExplorerN object is created to search the given path, and
 * all .h nad .cpp file will be stored at a list
 * RegularExp.h, a RegularExp object is created to select file which the file's name
 * matches to the given pattern.
 *
 * This package provides functions:
 * searchFile(vector)					store all valid file name in the vector
 * filterFile(vector, vector)		    store matching file's name and path in different vector
 * log(str)								print message to console
 *
 * Required Files:
 * ---------------
 * Loader.h, Loader.cpp
 * DirExplorerN.h, DirExplorerN.cpp
 * RegularExp.h, RegularExp.cpp
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
#include <vector>
#include "../FawcettPackage/DirExplorer-Naive/DirExplorerN.h"
#include "../RegularExp/RegularExp.h"


class Loader
{
	public:
		void searchFile(std::vector<std::string> &fileList, std::string filePath);

		int filterFile(std::vector<std::string> &fileList, std::vector<std::string> &filenameList, const std::string pattern);

		void log(std::string msg);
};

//----< print message to console >----------------------------------------------
inline void Loader::log(std::string msg)
{
	std::cout << "  " + msg + "  \n";
}

#pragma once
////////////////////////////////////////////////////////////////////////////
// PublisherFactory.h - the package contains a struct which is used to    //
//                      create and return an object of CodePublisher      //
// ver 1.0                                                                //
// Language:           C++, Visual Studio 2017                            //
// Application:        Project3, CSE687 - OOD Spring 2019                 //
// Author:             Yishi Lu, Syracuse University, EECS                //
//                     ylu154@syr.edu                                     //
////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * An struct which is used to create and return an object of 
 * CodePublihser
 *
 * This package provides following functions:
 * CreatePublisher()         accept two strings, and then create and return a object which is derived from CodePublisherInterface
 *
 * Required Files:
 * ---------------
 * CodePublisherInterface.h, CodePublisherInterface.cpp
 * PublisherFactory.h, PublisherFactory.cpp
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

#ifdef IN_DLL
#define DLL_DECL __declspec(dllexport)
#else
#define DLL_DECL __declspec(dllimport)
#endif

#include <string>
#include <iostream>
#include "../CodePublisherInterface/CodePublisherInterface.h"


struct PublisherFactory
{
	CodePublisherInterface* CreatePublisher(std::string path, std::string pattern);
};



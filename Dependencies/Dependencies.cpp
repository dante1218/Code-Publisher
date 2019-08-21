//////////////////////////////////////////////////////////////////////////////
// Dependency.cpp  - insert dependency link on #inclde tag of input file    //
// ver 1.0                                                                  //
// Language:    C++, Visual Studio 2017                                     //
// Application: Project3, CSE687 - OOD Spring 2019                          //
// Author:      Yishi Lu, Syracuse University, EECS                         //
//              ylu154@syr.edu                                              //
//////////////////////////////////////////////////////////////////////////////

#include "Dependencies.h"

std::string Dependencies::addDependenciesLink(std::string type, std::string nextLine)
{
	std::string link = type.substr(type.find("#") + 1, type.length() - 1);
	//log("dependency link: <a href='" + link + ".html>" + nextLine + "</a> is inserted by package Dependencies\n");
	return ("<a href='" + link + ".html'>" + nextLine + "</a>");
}


#ifdef TEST_DEPENDENCIES

int main()
{
	std::cout << "\n  Testing Dependencies";
	std::cout << "\n ====================================\n\n";

	Dependencies d;

	std::cout << "  --Test function addDependenciesLink():\n";
	std::string inputString = "include#myfolder/test.h";
	std::cout << "  Input: " + inputString + "\n" << "Output: " + d.addDependenciesLink(inputString, "#include '../myfolder/test.h'") << "\n\n";
}


#endif // TEST_DEPENDENCIES




///////////////////////////////////////////////////////////////////////////
// RegularExp.cpp - check input string is match to given pattern         //
// ver 1.0                                                               //
// Language:        C++, Visual Studio 2017                              //
// Application:     Project3, CSE687 - OOD Spring 2019                   //
// Author:          Yishi Lu, Syracuse University, EECS                  //
//                  ylu154@syr.edu                                       //
///////////////////////////////////////////////////////////////////////////


#include "RegularExp.h"

//----< check given string is match to given pattern >----------------------------------------------
bool RegularExp::matchPattern(std::string target, std::string pattern)
{
	try
	{
		std::regex reg(pattern);
		return regex_match(target, reg);
	}
	catch (const std::regex_error& e)
	{
		log("ERROR: The pattern is not valid regular expression. Please try another one.\n");
		(e);
		return false;
	}
	catch (...)
	{
		log("ERROR: Unexcepted exception.\n");
		return false;
	}
}

//----< check the pattern is valid regular expression >----------------------------------------------
bool RegularExp::checkPattern(std::string pattern)
{
	try
	{
		std::regex reg(pattern);
		return true;
	}
	catch (const std::regex_error& e)
	{
		log("ERROR: The pattern is not valid regular expression. Please try another one.\n");
		(e);
		return false;
	}
	catch (...)
	{
		log("ERROR: Unexcepted exception.\n");
		return false;
	}
}

#ifdef TEST_REGULAREXP
int main()
{
	std::cout << "\n  Testing RegularExp";
	std::cout << "\n ====================================\n\n";

	std::cout << "  Test function matchPattern():\n";
	RegularExp reg;
	if(reg.matchPattern("test.h", "(t)(.*)")) std::cout << "  input string test.h matches pattern (t)(.*)" << std::endl;
	else  std::cout << "  Not match\n";

	if(reg.matchPattern("test.h", "(A+).h")) std::cout << "  input string test.h matches pattern (.*)(.h)" << std::endl;
	else  std::cout << "  Not match\n"; 

	std::cout << std::endl;

	std::cout << "  Test function checkPattern():\n";
	if (reg.checkPattern("(")) std::cout << "  valid pattern" << std::endl;
	else std::cout << "  invalid pattern\n";

	if (reg.checkPattern("(A+).h")) std::cout << "  valid pattern" << std::endl;
	else std::cout << "  invalid pattern\n";
}
#endif

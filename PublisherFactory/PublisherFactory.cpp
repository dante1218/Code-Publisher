
////////////////////////////////////////////////////////////////////////////
// PublisherFactory.h - the package contains a struct which is used to    //
//                      create and return an object of CodePublisher      //
// ver 1.0                                                                //
// Language:           C++, Visual Studio 2017                            //
// Application:        Project3, CSE687 - OOD Spring 2019                 //
// Author:             Yishi Lu, Syracuse University, EECS                //
//                     ylu154@syr.edu                                     //
////////////////////////////////////////////////////////////////////////////

#include "PublisherFactory.h"
#include "../CodePublisher/CodePublisher.h"

//----< given sting of path and pattern to instantiate and return a CodePublisher object >----------------------------------------------
CodePublisherInterface* PublisherFactory::CreatePublisher(std::string path, std::string pattern)
{
	return new CodePublisher(path, pattern);
}

#ifdef PUBLISHERFACTORY_TEST
int main()
{
	std::cout << "\n  Testing PublisherFactory";
	std::cout << "\n  ====================================\n\n";

	PublisherFactory factory;
	CodePublisherInterface* test = factory.CreatePublisher("test_path", "test_pattern");
}
#endif // PUBLISHERFACTORY_TEST



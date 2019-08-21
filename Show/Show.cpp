///////////////////////////////////////////////////////////////////////
// Show.cpp  -  show a file in console or browser                    //
// ver 1.1                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Project3, CSE687 - OOD Spring 2019                   //
// Author:      Yishi Lu, Syracuse University, EECS                  //
//              ylu154@syr.edu                                       //
///////////////////////////////////////////////////////////////////////

#include "Show.h"
#include "../FawcettPackage/Process/Process.h"
#include "../FawcettPackage/FileSystem/FileSystem.h"

//----< check if the file is opened or not >----------------------------------------------
bool Show::checkIfstream(std::ifstream &in, std::string fileName)
{
	if (!in.good()) {
		log("ERROR: " + fileName + " cannot be opened. \n");
		return false;
	}
	return true;
}

//----< For demonstration convertion, print content of a converted file to console >----------------------------------------------
void Show::demoConvertion(std::string file)
{
	char nextChar;
	std::ifstream convertedFile(file);
	if (!checkIfstream(convertedFile, file)) return;

	log("-------------------- Following shows The content of processed file >>> " + file + ".html <<< --------------------\n");
	while (convertedFile.get(nextChar)) std::cout << nextChar;
	std::cout << "\n\n\n\n";
	convertedFile.close();
	log("-------------------- End of printing the content of processed file >>> " + file + ".html <<< --------------------\n");
}

//----< display content of file by given application >----------------------------------------------
void Show::showHTML(const std::string file, std::string browserLocation)
{
	Process p; //create Process object to use given application to display file content
	std::string appPath = browserLocation;
	p.application(appPath);
	
	log("Showing processed file " + file + " by application: " + appPath + ".\n\n");

	std::string filePath = "  --new-window \"" + FileSystem::Path::getFullFileSpec(file) + '"';
	p.commandLine(filePath);

	p.create();
	CBP callback = []() { std::cout << "\n  --- child process exited with this message ---\n"; };
	p.setCallBackProcessing(callback);
	p.registerCallback();

	WaitForSingleObject(p.getProcessHandle(), INFINITE);  // wait for created process to terminate
}

#ifdef TEST_SHOW
int main()
{
	std::cout << "\n  Testing Display";
	std::cout << "\n ====================================\n\n";

	Show sh;

	std::cout << "  Test function showHTML():\n";
	sh.showHTML("..//test//Converter.cpp.html", "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe");

	std::cout << "  Test function demoConvertion():\n";
	sh.demoConvertion("..//test//Converter.cpp.html");	
}
#endif

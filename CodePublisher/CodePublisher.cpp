
////////////////////////////////////////////////////////////////////////
// CodePublisher.cpp - accept file path and pattern from user, and    //
//                     then find and convert valid file to a valid    //
//                     html file and insert dependency link and       //
//                     wrapping div                                   //
// ver 1.0                                                            //
// Language:     C++, Visual Studio 2017                              //
// Application:  Project3, CSE687 - OOD Spring 2019                   //
// Author:       Yishi Lu, Syracuse University, EECS                  //
//               ylu154@syr.edu                                       //
////////////////////////////////////////////////////////////////////////

#include "CodePublisher.h"

//----< constructor, accepting input path and pattern >----------------------------------------------
CodePublisher::CodePublisher(std::string input_path, std::string input_pattern) {
	path = input_path;
	pattern = input_pattern;
	browserLocation = "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe";

	createFolder("convertedPages"); //create storing folder
	log("A CodePublisher object is created with path:" + path + ", pattern:" + pattern + "\n");
}

//----< create a folder by given the name >----------------------------------------------
void CodePublisher::createFolder(std::string folderName)
{
	storingFolder = folderName;
	folderName = "..\\" + folderName;
	std::wstring temp = std::wstring(folderName.begin(), folderName.end());

	if (CreateDirectory(temp.c_str(), NULL))
		std::cout << "  Successfully created folder /" + storingFolder + ". Using it to store processed file.\n\n";
	else
		std::cout << "  /" + storingFolder + " already exists. Using it to store processed file.\n\n";
}

//----< function used to set target path and pattern >----------------------------------------------
void CodePublisher::acceptInput(std::string input_path, std::string input_pattern) {
	path = input_path;
	pattern = input_pattern;
	log("Accept inputs from user, path:" + input_path + ", pattern:" + input_pattern + "\n");
}

//----< find all .h and .cpp file which is match to the pattern >----------------------------------------------
bool CodePublisher::findValidFile()
{
	log("Searching files in the given path (" + path + ") by Loader package");
	log("------------------------------------------------------------------");
	find.searchFile(filePath, path);

	for (auto f : filePath) std::cout << "  -- " << f << "\n";
	std::cout << "\n\n";

	int numOfValidFile = find.filterFile(filePath, filenameList, pattern);

	if (numOfValidFile <= 0)
	{
		//there is no valid file, error message will be print
		if(numOfValidFile != -999999) log("ERROR: No Maching file is found. Please try another directory.\n");
		filePath.clear();
		filenameList.clear();
		return false;
	}
	else
	{
		std::cout << "  There are " << numOfValidFile;
		log("matching files. \n\n\n");
		return true;
	}
}

//----< converter all valid file to html file and store them in the "storingFolder" >----------------------------------------------
void CodePublisher::converterFile()
{
	int count = 1;

	log("Starting analysis and process files");
	log("-----------------------------------");
	for (auto f : filePath)
	{
		Analysis analy;
		analy.analysisFile(path, f, filenameList);
		conv.makeHTML(f, storingFolder, path, analy);
		analy.reset();
		count++;
		std::cout << "  -- Processed: " << f;
	}
	log("\n\n  Analysis and processing are finished.");
	log("-------------------------------------------\n");

	filePath.clear();
	filenameList.clear();
}

//----< display a sample of processed file, print on the console and show in the brower >----------------------------------------------
void CodePublisher::showProcessedFile(std::string filename)
{
	//log("Showing selected file with browser:");
	//filename = "..//" + storingFolder + "//" + filename;
	sh.showHTML(filename, browserLocation);
}

#ifdef CODEPUBLISHER_TEST

int main()
{
	std::cout << "\n  Testing CodePublisher";
	std::cout << "\n  ====================================\n\n";

	std::string path = "..//", pattern = "[A].*";

	std::cout << "  --Test function CodePublisher():\n";
	CodePublisher cod("", "");

	std::cout << "  --Test function createFolder():\n";
	cod.createFolder("test");

	std::cout << "  --Test function acceptInput():\n";
	cod.acceptInput(path, pattern);

	std::cout << "  --Test function findValidFile():\n";
	cod.findValidFile();

	std::cout << "  --Test function converterFile():\n";
	cod.converterFile();

	std::cout << "  --Test function showProcessedFile():\n";
	cod.showProcessedFile("Analysis.h.html");
}

#endif // CODEPUBLISHER_TEST



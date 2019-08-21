///////////////////////////////////////////////////////////////////////
// ServerPrototype.cpp - Console App that processes incoming messages//
// ver 1.0                                                           //
// Author: Yishi Lu, CSE687 OOD, Spring 2019                         //
// Source: Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018 //
///////////////////////////////////////////////////////////////////////

#include "Server.h"
#include "../FawcettPackage/FileSystem/FileSystem.h"
#include <chrono>

namespace MsgPassComm = MsgPassingCommunication;

using namespace Repository;
using namespace FileSystem;
using Msg = MsgPassingCommunication::Message;

//----< returen file by given path >------------------
Files Server::getFiles(const Repository::SearchPath& path)
{
	return Directory::getFiles(path);
}

//----< return directory by given path>------------------
Dirs Server::getDirs(const Repository::SearchPath& path)
{
	return Directory::getDirectories(path);
}

//----< print message on console >------------------
template<typename T>
void show(const T& t, const std::string& msg)
{
	std::cout << "\n  " << msg.c_str();
	for (auto item : t)
	{
		std::cout << "\n    " << item.c_str();
	}
}

//----< function for echo message testing >------------------
std::function<Msg(Msg)> echo = [](Msg msg) {
	Msg reply = msg;
	reply.to(msg.from());
	reply.from(msg.to());
	return reply;
};

//----< receive command from client and send desired files' name to client >------------------
std::function<Msg(Msg)> getFiles = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getFiles");
	std::string path = msg.value("path");
	if (path != "")
	{
		std::string searchPath = path;
		
		Files files = Server::getFiles(searchPath);
		size_t count = 0;
		for (auto item : files)
		{
			std::string countStr = Utilities::Converter<size_t>::toString(++count);
			reply.attribute("file" + countStr, item);
		}
	}
	else
	{
		std::cout << "\n  getFiles message did not define a path attribute";
	}
	return reply;
};

//----< receive command from client and send desired directories' name to client >------------------
std::function<Msg(Msg)> getDirs = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getDirs");
	std::string path = msg.value("path");
	if (path != "")
	{
		std::string searchPath = path;
		Files dirs = Server::getDirs(searchPath);
		size_t count = 0;
		for (auto item : dirs)
		{
			if (item != ".." && item != ".")
			{
				std::string countStr = Utilities::Converter<size_t>::toString(++count);
				reply.attribute("dir" + countStr, item);
			}
		}
	}
	else
	{
		std::cout << "\n  getDirs message did not define a path attribute";
	}
	return reply;
};

//----< receive command from client and send all converted files' name to client >------------------
std::function<Msg(Msg)> getConvertedFiles = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getConvertedList");

	Files files = Server::getFiles(pathName);
	size_t count = 0;
	for (auto item : files)
	{
		if (item != ".." && item != ".")
		{
			std::string countStr = Utilities::Converter<size_t>::toString(++count);
			reply.attribute("convertedList" + countStr, item);
		}
	}

	return reply;
};

//----< receive command from client and convert all required file by calling function from Code Publisher >------------------
std::function<Msg(Msg)> publishDirs = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("publishDirs");
	std::string path = msg.value("path");
	std::string pattern = msg.value("pattern");
	if (path != "" && pattern != "")
	{
		PublisherFactory factory;

		CodePublisherInterface* publisher = factory.CreatePublisher(path, pattern);
		if (!publisher->findValidFile()) {
			reply.attribute("publishResult" , "0");
		}
		else
		{
			publisher->converterFile();
			reply.attribute("publishResult", "1");
		}
	}
	else
	{
		std::cout << "\n  publishDirs message did not define path and pattern attribute";
	}
	return reply;
};

//----< receive command from client and send desired file (real file, not name) to client >------------------
std::function<Msg(Msg)> downloadFile = [](Msg msg) {
	Msg reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("downLoadFile");
	std::string fileName = msg.value("fileName");

	if (fileName != "")
	{
		reply.file(fileName);
	}
	else
	{
		std::cout << "\n  downLoadFile message did not define a fileName attribute";
	}
	return reply;
};

int main(int argc, char **argv)
{
	if (argc <= 2)
	{
		std::cout << "  ERROE: Missing Command Line Argument!\n  Please provide Server address and port number! \n\n";
		system("pause");
		exit(-1);
	}

	std::string address = argv[1];
	int portNumber = atoi(argv[2]);
	const MsgPassingCommunication::EndPoint serverEndPoint(address, portNumber);

	std::cout << "  Demonstration of Requierment #3: Client-Server configuration\n";
	std::cout << "  ============================================================\n";
	std::cout << "  There Client-Server architectures, client send request and server call CodePublisher to process the request. Asynchronous communication is supported.\n\n";

	std::cout << "  Demonstration of Requierment #4: Client GUI\n";
	std::cout << "  ===========================================\n";
	std::cout << "  Client GUI is implemented, it supports navigating remote directories to find a project for conversion, and supports displaying the conversion results in a way that meets Project #3 requirements.\n\n";

	std::cout << "  Demonstration of Requierment #5: Providing message designs\n";
	std::cout << "  ==========================================================\n";
	std::cout << "  Several message designs are implemented; getFiles, getDirs, getConvertedFiles, publishDirs, and downloadFile\n\n";

	std::cout << "  Demonstration of Requierment #6: Files converting and transfering\n";
	std::cout << "  =================================================================\n";
	std::cout << "  publishDirs supports to convert client requested files, and downloadFile supports to send converted file back to client\n\n";

	std::cout << "  Demonstration of Requierment #7: Multiple clients\n";
	std::cout << "  =================================================\n";
	std::cout << "  Multiple clients is supported. In auto test, we run two client GUI to show the satisfaction of this requirement\n\n\n";

	std::cout << "  Demonstration of Requierment #8: Auto test\n";
	std::cout << "  =================================================\n";
	std::cout << "  Please check the server console, client GUI and GUI console to see the auto test result\n\n";

	Server server(serverEndPoint, "CodePublisherServer");
	server.start();
	std::cout << "\n  Server start";
	std::cout << "\n ----------------------------";
	server.addMsgProc("echo", echo);
	server.addMsgProc("getFiles", getFiles);
	server.addMsgProc("getDirs", getDirs);
	server.addMsgProc("getConvertedFile", getConvertedFiles);
	server.addMsgProc("publishDirs", publishDirs);
	server.addMsgProc("downloadFile", downloadFile);
	server.addMsgProc("serverQuit", echo);
	server.processMessages();

	server.stop();
	return 0;
}


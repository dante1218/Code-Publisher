///////////////////////////////////////////////////////////////////////
// Display.h  - insert <div> to wrapping comment, function and class //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Project3, CSE687 - OOD Spring 2019                   //
// Author:      Yishi Lu, Syracuse University, EECS                  //
//              ylu154@syr.edu                                       //
///////////////////////////////////////////////////////////////////////

#include "Display.h"

//----< add wripping <div> for class and function >----------------------------------------------
std::string Display::addClassFunctionDiv(std::string type, std::string nextLine)
{
	std::string sub1 = "", sub2 = "";
	sub1 = nextLine.substr(0, nextLine.find("{"));
	sub2 = nextLine.substr(nextLine.find("{") + 1, nextLine.length());
	if (type == "classOneLine") {
		return (sub1 + "<div class=\"toggleClassDisplay\" style = \"display: inline;\">" + "{" + sub2 + "</div>");
	}
	else if (type == "functionOneLine") {
		std::size_t found = nextLine.find_first_not_of(" ");
		if (nextLine[found] == ':') {
			return ("<div class=\"toggleFunctionDisplay\" style = \"display: inline;\">" + nextLine + "</div>");
		}
		return (sub1 + "<div class=\"toggleFunctionDisplay\" style = \"display: inline;\">" + "{" + sub2 + "</div>");
	}
	else if (type == "classStart") {
		return (sub1 + "<div class=\"toggleClassDisplay\" style = \"display: inline;\">" + "{"+ sub2 );
	}
	else if (type == "functionStart") {
		std::size_t found = nextLine.find_first_not_of(" ");
		if (nextLine[found] == ':') {
			return ("<div class=\"toggleFunctionDisplay\" style = \"display: inline;\">" + nextLine);
		}
		return (sub1 + "<div class=\"toggleFunctionDisplay\" style = \"display: inline;\">" + "{" + sub2);
	}
	else if (type == "classEnd") {
		return (nextLine + "</div>");
	}
	else if (type == "functionEnd") {
		return (nextLine + "</div>");
	}
	return nextLine;
}

//----< add wripping <div> for comment >----------------------------------------------
std::string Display::addCommentDiv(std::string type, std::string nextLine)
{
	std::string sub1 = "", sub2 = "", sub3 = "";
	if (type == "singleLineComment") {
		sub1 = nextLine.substr(0, nextLine.find("//"));
		sub2 = nextLine.substr(nextLine.find("//"), nextLine.length());
		return (sub1 + "<div class=\"toggleCommentDisplay\" style = \"display: inline;\">" + sub2 + "</div>");
	}
	else if (type == "oneLineComment") {
		sub1 = nextLine.substr(0, nextLine.find("/*"));
		sub2 = nextLine.substr(nextLine.find("/*"), nextLine.find("*/") - nextLine.find("/*") + 2);
		sub3 = nextLine.substr(nextLine.find("*/") + 2, nextLine.length());
		return (sub1 + "<div class=\"toggleCommentDisplay\" style = \"display: inline;\">" + sub2 + "</div>" + sub3);
	}
	else if (type == "commentStart") {
		return ("<div class=\"toggleCommentDisplay\" style = \"display: inline;\">" + nextLine);
	}
	else if (type == "commentEnd") {
		return (nextLine + "</div>");
	}
	return nextLine;
}

#ifdef TEST_DISPLAY
int main()
{
	std::cout << "\n  Testing Display";
	std::cout << "\n ====================================\n\n";

	Display dis;

	std::cout << "  Test function addClassFunctionDiv():\n";

	std::string oneLineClass = "class test{}";
	std::cout << "  Input: " + oneLineClass + "\n" << "  Output: " + dis.addClassFunctionDiv("classOneLine", oneLineClass) << "\n\n";

	std::string oneLineFunction = "void test(){}";
	std::cout << "  Input: " + oneLineFunction + "\n" << "  Output " + dis.addClassFunctionDiv("functionOneLine", oneLineFunction) << "\n\n";

	std::string classStart = "class test {";
	std::cout << "  Input: " + classStart + "\n" << "  Output " + dis.addClassFunctionDiv("classStart", classStart) << "\n\n";

	std::string classEnd = "};";
	std::cout << "  Input: " + classEnd + "\n" << "  Output " + dis.addClassFunctionDiv("classEnd", classEnd) << "\n\n";

	std::string functionStart = "void test() {";
	std::cout << "  Input: " + functionStart + "\n" << "  Output " + dis.addClassFunctionDiv("functionStart", functionStart) << "\n\n";

	std::string functionEnd = "}";
	std::cout << "  Input: " + functionEnd + "\n" << "  Output " + dis.addClassFunctionDiv("functionEnd", functionEnd) << "\n\n";

	std::cout << "  Test function addCommentDiv():\n";

	std::string commentStart = "/*test test";
	std::cout << "  Input: " + commentStart + "\n" << "  Output " + dis.addCommentDiv("commentStart", commentStart) << "\n\n";

	std::string commentEnd = "test test*/";
	std::cout << "  Input: " + commentEnd + "\n" << "  Output " + dis.addCommentDiv("commentEnd", commentEnd) << "\n\n";

	std::string oneLineComment = "/*test test*/";
	std::cout << "  Input: " + oneLineComment + "\n" << "  Output " + dis.addCommentDiv("oneLineComment", oneLineComment) << "\n\n";

	std::string singleLineComment = "123456 //test test";
	std::cout << "  Input: " + singleLineComment + "\n" << "  Output " + dis.addCommentDiv("singleLineComment", singleLineComment) << "\n\n";
}
#endif //TEST_DISPLAY


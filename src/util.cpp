#include <iostream>
#include <fstream>
#include <sstream>
#include "util.h"

std::string readFile(std::string path)
{
	std::string str;
	std::ifstream file(path);
	if (!file)
	{
		std::cerr << "Unable to open file: " << path << std::endl;
		return "";
	}

	std::ostringstream contents;
	contents << file.rdbuf();
	return contents.str();
}
#include "level.h"
#include <fstream>
#include <iostream>

void level::loadfromfile(std::string filepath)
{
	std::ifstream TestFile;
	TestFile.open(filepath);
	if (!TestFile)
	{
		return;
	}

	getline(TestFile, *levelfile);
}
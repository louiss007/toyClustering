#pragma once
#include <string>
#include <vector>
using namespace std;

class utils
{
public:
	utils();
	~utils();
	static vector<string> parseArgs(int argc, char *argv[]);
};


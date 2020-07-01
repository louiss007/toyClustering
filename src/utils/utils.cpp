#include "../../include/utils/utils.h"


utils::utils()
{
}


utils::~utils()
{
}

vector<string> utils::parseArgs(int argc, char *argv[]) {
	vector<string> args;
	for (int i = 1; i < argc; ++i)
	{
		args.push_back(string(argv[i]));
	}
	return args;
}
#pragma once
#include <map>
#include <string>
using namespace std;

class ClusterSample
{
public:
	ClusterSample(const string &line);
	~ClusterSample();

public:
	map<string, double> x;
	static const string spliter;
	static const string innerSpliter;
};


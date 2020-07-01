#include "../../include/sample/ClusterSample.h"
#include <iostream>
using namespace std;


const string ClusterSample::spliter = " ";
const string ClusterSample::innerSpliter = ":";

ClusterSample::ClusterSample(const string& line)
{
	this->x.clear();
	size_t posb = 0;
	size_t pose = 0;
	string index;
	double value;
	while (pose < line.length()) {
		posb = line.find_first_not_of(this->spliter, pose);
		
		if (posb == string::npos) {
			break;
		}
		pose = line.find_first_of(this->innerSpliter, posb);
		if (pose == string::npos) {
			cerr << "wrong line of sample input: " << line << endl;
			exit(-1);
		}
		
		index = line.substr(posb, pose - posb);
		posb = pose + 1;
		if (posb >= line.length()) {
			cerr << "wrong line of sample input: " << line << endl;
			exit(-1);
		}
		pose = line.find_first_of(spliter, posb);
		value = stod(line.substr(posb, pose - posb));
		if (value != 0) {
			this->x.insert(pair<string, double>(index, value));
		}
	}
}


ClusterSample::~ClusterSample()
{
}

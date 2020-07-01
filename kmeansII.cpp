#include <map>
#include <iostream>
#include <algorithm>
#include "include/sample/ClusterSample.h"
using namespace std;

void test() {
	string line = "1:0.1 2:0.3 3:0.5";
	ClusterSample *sample = new ClusterSample(line);
	for (auto kv : sample->x) {
		cout << kv.first << ":" << kv.second << endl;
	}
}
int main()
{
	test();
    return 0;
}


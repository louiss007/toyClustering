// kmeansII.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <map>
#include <iostream>
#include <algorithm>
#include "ClusterSample.h"
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


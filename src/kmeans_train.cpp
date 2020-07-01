#include "../include/model/kmeans.h"
#include "../include/utils/utils.h"
#include <iostream>
#include <string>
using namespace std;

string help() {
	string helpInfo(
		"\nusage: ./kmeans_train [options]"
		"\n"
		"options:\n"
		"-m [model]: output model\n"
		"-k [number]: the number of cluster\n"
		"-n [maxIter]: iterations of training model\n"
		"-t [trainFile]: data file for training\n"
		"-p [predictFile]: test file for predict\n"
		"-r [resultFile]: result File of prediction output\n"
	);
	return helpInfo;
}

int train(TrainOption & arg) {
	kmeans *kmodel = new kmeans(arg.k, arg.maxIter);
	if (arg.flag != "train") {
		cout << "task type is wrong, -f flag should be set train!" << endl;
	}
	vector<Point*> trainSet = kmodel->loadData(arg.trainFile);
	kmodel->ktrain(trainSet, arg.k, arg.maxIter);
	kmodel->saveModel(arg.modelPath);
}

int main(int argc, char *argv[]) {
	TrainOption trainOpt;
	try
	{
	    vector<string> optVec = utils::parseArgs(argc, argv);
		trainOpt.parse(optVec);
	}
	catch (const invalid_argument& e)
	{
		cerr << "invalid_argument:" << e.what() << endl;
		cerr << help() << endl;
		return -1;
	}
	train(trainOpt);
	return 0;
}

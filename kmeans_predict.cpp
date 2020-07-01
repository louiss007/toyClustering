#include "kmeans.h"
#include "utils.h"
#include <iostream>
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

int predict(TrainOption & arg) {
	kmeans *kmodel = new kmeans(arg.k, arg.maxIter);
	if (arg.flag != "test") {
		cout << "task type is wrong, -f flag should be set test!" << endl;
	}
	kmodel->loadModel(arg.modelPath);
	kmodel->kpredictBatch(arg.testFile, arg.resultFile);
}

int main(int argc, char *argv[]) {
	TrainOption trainOpt;
	try
	{
		trainOpt.parse(utils::parseArgs(argc, argv));
	}
	catch (const invalid_argument& e)
	{
		cerr << "invalid_argument:" << e.what() << endl;
		cerr << help() << endl;
		return -1;
	}
	predict(trainOpt);
}

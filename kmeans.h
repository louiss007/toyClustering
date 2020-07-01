#pragma once
#include <vector>
#include <map>
#include <string>
using namespace std;

struct Point {
	map<string, double> point;// because compute the sim of two points with the index, so not use vector<pair<string, double>>
	Point(map<string, double> val):point(val) {}
};

struct Cluster {
	int clusterIndex;
	map<string, double> cluster;
	Cluster(int val, Point *p) :clusterIndex(val) {
		this->cluster = p->point;
	}
};


class kmeans
{
public:
	kmeans(int k, int maxIter);
	~kmeans();
	map<int, Cluster*> kinit(vector<Point*> &newPoints, int k);
	double computeSim(Point *p1, Cluster* p2);
	void updateCordinate(Cluster* cluster, vector<Point*> &point);
	void updateCluster(map<int, vector<Point*>> &cluster2point, map<int, Cluster*> &index2kclusters);
	map<int, Cluster*> ktrain(vector<Point*> &points, int &kcluster, int &maxIter);
	vector<Point*> loadData(string inFile);
	void saveModel(string modelName);
	void loadModel(string model);
	int kpredict(Point *point);
	void kpredictBatch(string testFile, string outFile);
	void parseHeadInfo(string line);

private:
	map<int, Cluster*> index2kclusters;
	int k;
	int maxIter;
};

struct TrainOption {
	int k;
	int maxIter;
	string modelPath;
	string trainFile;
	string testFile;
	string flag;
	string resultFile;
	TrainOption() :k(10), maxIter(10) {}
	void parse(vector<string> &args) {
		int argc = args.size();
		if (argc == 0) {
			throw invalid_argument("invalid command\n");
		}
		for (int i = 0; i < argc; i++) {
			if (args[i] == "-k") {
				if (i == argc - 1) {
					throw invalid_argument("invalid argument\n");
				}
				this->k = stoi(args[++i]);
			}
			else if (args[i] == "-n") {
				if (i == argc - 1) {
					throw invalid_argument("invalid argument\n");
				}
				this->maxIter = stoi(args[++i]);
			}
			else if (args[i] == "-m") {
				if (i == argc - 1) {
					throw invalid_argument("invalid argument\n");
				}
				this->modelPath = args[++i];
			}
			else if (args[i] == "-t") {
				if (i == argc - 1) {
					throw invalid_argument("invalid argument\n");
				}
				this->trainFile = args[++i];
			}
			else if (args[i] == "-p") {
				if (i == argc - 1) {
					throw invalid_argument("invalid argument\n");
				}
				this->testFile = args[++i];
			}
			else if (args[i] == "-f") {
				if (i == argc - 1) {
					throw invalid_argument("invalid argument\n");
				}
				this->flag = args[++i];
			}
			else if (args[i] == "-r") {
				if (i == argc - 1) {
					throw invalid_argument("invalid argument\n");
				}
				this->resultFile = args[++i];
			}
			else {
				throw invalid_argument("invalid command\n");
				break;
			}
		}
	}
};
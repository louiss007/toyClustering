#include "../../include/model/kmeans.h"
#include "../../include/sample/ClusterSample.h"
#include <set>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include  <climits>
using namespace std;


kmeans::kmeans(int k, int maxIter)
{
	this->k = k;
	this->maxIter = maxIter;
}


kmeans::~kmeans()
{
}

map<int, Cluster*> kmeans::kinit(vector<Point*> &points, int k){
	map<int, Cluster*> kcluster;
	int n = points.size();
	set<int> initIndexSet;
	while (true) {
		if (initIndexSet.size() == k) break;
		int index = rand() % n;
		if (initIndexSet.find(index) == initIndexSet.end()) {
			initIndexSet.insert(index);
		}
	}
	int i = 0;
	for (int index : initIndexSet) {
		Cluster *cluster = new Cluster(index, points[index]);
		cluster->clusterIndex = ++i;
		kcluster[i] = cluster;
	}
	return kcluster;
}

double kmeans::computeSim(Point *p1, Cluster* p2){
	map<string, double> mergePoint = p2->cluster;
	for (auto kv : p1->point) {
		if (mergePoint.find(kv.first) != mergePoint.end()) {
			mergePoint[kv.first] -= kv.second;
		}
	}
	double sqrtSum = 0.0;
	for (auto kv : mergePoint) {
		sqrtSum += pow(kv.second, 2);
	}
	return sqrtSum;
}

void kmeans::updateCordinate(Cluster* cluster, vector<Point*> &point) {
	int n = point.size();
	map<string, double> newPoint;

	for (Point* p : point) {
		for (auto kv : p->point) {
			if (newPoint.find(kv.first) != newPoint.end()) {
				newPoint[kv.first] += kv.second;
			}
		}
	}
	for (auto kv : newPoint) {
		kv.second /= n;
	}
	cluster->cluster = newPoint;
}

void kmeans::updateCluster(map<int, vector<Point*>> &cluster2point, map<int, Cluster*> &index2kclusters){
	for (auto kv : cluster2point) {
		int index = kv.first;
		vector<Point*> points = kv.second;
		Cluster *cluster = index2kclusters[index];
		this->updateCordinate(cluster, points);
	}
}

map<int, Cluster*> kmeans::ktrain(vector<Point*> &points, int &kcluster, int &maxIter){
	this->index2kclusters = this->kinit(points, kcluster);
	map<int, vector<Point*>> cluster2point;
	int i = 0;
	while (i < maxIter) {
		for (auto point : points) {
			int index = -1;
			double dis = LONG_MAX;
			for (auto kv : this->index2kclusters) {
				Cluster *cluster = kv.second;
				int cIndex = kv.first;
				double distance = this->computeSim(point, cluster);
				if (distance < dis) {
					dis = distance;
					index = cIndex;
				}
			}
			cluster2point[index].push_back(point);
		}
		this->updateCluster(cluster2point, this->index2kclusters);
		i++;
	}
	return this->index2kclusters;
}

vector<Point*> kmeans::loadData(string inFile){
	ifstream in(inFile);
	if (!in.is_open()) {
		cout << "can not open train file " << inFile << endl;
		in.close();
		exit(-1);
	}
	vector<Point*> samples;
	string line;
	while (getline(in, line)) {
		ClusterSample *sample = new ClusterSample(line);
		Point *point = new Point(sample->x);
		samples.push_back(point);
	}
	return samples;
}

void kmeans::saveModel(string modelName){
	ofstream out(modelName, ios::out);
	if (!out.is_open()) {
		cout << "can not open model file, no enough space " << modelName << endl;
		out.close();
		exit(-1);
	}
	out << "k:" << this->k << " " << "iter:" << this->maxIter << endl;
	for (auto kv : this->index2kclusters) {
		out << kv.second->clusterIndex << " ";
		int n = kv.second->cluster.size();
		int i = 0;
		for (auto kkv: kv.second->cluster) {
			if (i == n - 1) {
				out << kkv.first << ":" << kkv.second << endl;
			}
			else {
				out << kkv.first << ":" << kkv.second << " ";
			}
			i++;
		}
		out.close();
	}
}

void kmeans::loadModel(string model){
	ifstream in(model);
	if (!in.is_open()) {
		cout << "can not open model file " << model << endl;
		in.close();
		exit(-1);
	}

	//kmeans *kmodel = new kmeans(k, maxIter);
	string line;
	getline(in, line);
	if (line.find("k") == string::npos || line.find("iter") == string::npos) {
		cout << "model format is not right,should contain head info!" << endl;
		exit(-1);
	}
	parseHeadInfo(line);
	while (getline(in, line)) {
		int pose = line.find_first_of(" ", 0);
		int clusterIndex = stoi(line.substr(0, pose - 0));
		ClusterSample *partModel = new ClusterSample(line.substr(pose + 1));
		Point *point = new Point(partModel->x);
		Cluster *cluster = new Cluster(clusterIndex, point);
		this->index2kclusters.insert(pair<int, Cluster*>(clusterIndex, cluster));
	}
	in.close();
	//return kmodel;
}

int kmeans::kpredict(Point *point){
	int targetClusterIndex = -1;
	long long minDis = LONG_MAX;
	for (auto kv : this->index2kclusters) {
		int index = kv.first;
		Cluster *cluster = kv.second;
		double dis = this->computeSim(point, cluster);
		if (dis < minDis) {
			minDis = dis;
			targetClusterIndex = kv.second->clusterIndex;
		}
	}
	return targetClusterIndex;
}

void kmeans::kpredictBatch(string testFile, string outFile){
	ifstream in(testFile);
	if (!in.is_open()) {
		cout << "can not open test file " << testFile << endl;
		in.close();
		exit(-1);
	}
	ofstream out(outFile, ios::out);
	if (!out.is_open()) {
		cout << "can not open result file " << outFile << endl;
		out.close();
		exit(-1);
	}
	string line;
	while (getline(in, line)) {
		ClusterSample *sample = new ClusterSample(line);
		Point *point = new Point(sample->x);
		int targetCluster = this->kpredict(point);
		out << targetCluster << endl;
	}
	in.close();
	out.close();
}

void kmeans::parseHeadInfo(string line) {
	size_t posb = 0;
	size_t pose = 0;
	string index;
	double value;
	while (pose < line.length()) {
		posb = line.find_first_not_of(" ", pose);

		if (posb == string::npos) {
			break;
		}
		pose = line.find_first_of(":", posb);
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
		pose = line.find_first_of(" ", posb);
		value = stoi(line.substr(posb, pose - posb));
		if (index == "k") {
			this->k = value;
		}
		else if (index == "iter") {
			this->maxIter = value;
		}
		else {
			cout << "wrong info in model head info!" << endl;
			exit(-1);
		}
	}
}
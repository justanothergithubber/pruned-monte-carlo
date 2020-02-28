#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include "pmc.hpp"

// Streams
using std::cerr;
using std::cout;
// Functions
using std::endl;
using std::make_pair;
// Classes
using std::string;
using std::ifstream;
using std::vector;
using std::pair;

int main(int argc, char **argv) {
	if (argc < 4) {
		cerr << "./pmc graph k R" << endl;
		exit(1);
	}

	string file = argv[1];
	int k = atoi(argv[2]);
	int R = atoi(argv[3]);

	ifstream is(file.c_str());
	vector<pair<pair<int, int>, double> > es;
	int u, v;
	double p;
	for (; is >> u >> v >> p;) {
		if (u == v) {
			continue;
		}
		es.push_back(make_pair(make_pair(u, v), p));
	}
	is.close();

	InfluenceMaximizer im;
	pair<vector<int>, vector<double> > inf_max_res = im.run(es, k, R);
	for (int i = 0; i < k; i++) {
		cout << i << "-th seed and marginal gain =\t" << inf_max_res.first[i] << "\t" << inf_max_res.second[i] << endl;
	}

	return 0;
}

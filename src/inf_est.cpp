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
		cerr << "./pmc graph seed_set_file R" << endl;
		exit(1);
	}

	string graph_file = argv[1];
	string seed_file = argv[2];
	int R = atoi(argv[3]);

	ifstream is(graph_file.c_str());
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

	ifstream sf(seed_file.c_str());
	vector<int> seeds;
	int seed;
    while ( sf >> seed ) {
        seeds.push_back(seed);
    }
	sf.close();

	InfluenceMaximizer im;
	vector<double> inf_max_res = im.est(es, seeds, R);
	int k = seeds.size();
	for (int i = 0; i < k; i++) {
		cout << "Marginal gain of seed " << seeds[i] << " =\t" << inf_max_res[i] << endl;
	}

	return 0;
}

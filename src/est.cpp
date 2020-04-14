#include <iostream>
#include <fstream>
#include <vector>
#include "pmc.hpp"

int main(int argc, char **argv) {
	if (argc < 5) {
		std::cerr << "./pmc_est graph seed_set_file R seed_delta" << std::endl;
		exit(1);
	}

	std::string graph_file = argv[1];
	std::string seed_file = argv[2];
	int R = atoi(argv[3]);
	const int seed_delta = atoi(argv[4]);

	std::ifstream is(graph_file.c_str());
	std::vector<std::pair<std::pair<int, int>, double> > es;
	int u, v;
	double p;
	for (; is >> u >> v >> p;) {
		if (u == v) {
			continue;
		}
		es.push_back(std::make_pair(std::make_pair(u, v), p));
	}
	is.close();

	std::ifstream sf(seed_file.c_str());
	std::vector<unsigned int> seeds;
	int seed;
	while ( sf >> seed ) {
		seeds.push_back(static_cast<unsigned int>(seed));
	}
	sf.close();

	InfluenceMaximizer im;
	std::vector<double> inf_max_res =
		im.est(es, seeds, R, seed_delta);
	unsigned long long k = seeds.size();
	for (unsigned int i = 0; i < k; i++) {
		std::cout << seeds[i] << "\t"
			<< inf_max_res[i] << "\t" << std::endl;
	}

	return 0;
}

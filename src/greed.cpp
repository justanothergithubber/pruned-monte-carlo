#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <chrono>
#include "pmc.hpp"

int main(int argc, char **argv) {
	if (argc < 5) {
		std::cerr << "./pmc_greed tsv_file target_seed_size "
					 "number_of_random_graphs seed_delta" << std::endl;
		exit(1);
	}

	const std::chrono::high_resolution_clock::time_point 
		start_time = std::chrono::high_resolution_clock::now();

	std::string file = argv[1];
	int k = atoi(argv[2]);
	int R = atoi(argv[3]);
	const int seed_delta = atoi(argv[4]);

	std::ifstream is(file.c_str());
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

	InfluenceMaximizer im;
	std::tuple<std::vector<int>, std::vector<double>, std::vector<double> >
		inf_max_res = im.run(es, k, R, seed_delta, start_time);
	for (int i = 0; i < k; i++) {
		std::cout << std::get<0>(inf_max_res)[i] << "\t"
			<< std::get<1>(inf_max_res)[i] << "\t"
			<< std::get<2>(inf_max_res)[i] << std::endl;
	}

	return 0;
}

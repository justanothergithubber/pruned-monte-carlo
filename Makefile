CXX = g++
CXXFLAGS = -g -Wall -Wextra -O3

all: pmc_greed pmc_est

pmc_greed: src/greed.cpp src/pmc.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

pmc_est: src/inf_est.cpp src/pmc.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f pmc_greed
	rm -f pmc_est

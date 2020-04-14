CXX = g++
CXXFLAGS = -Wall -Wextra -Wconversion -Werror -pedantic -std=c++17 -O3 

all: pmc_greed pmc_est

pmc_greed: src/greed.cpp src/pmc.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

pmc_est: src/est.cpp src/pmc.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f pmc_greed
	rm -f pmc_est

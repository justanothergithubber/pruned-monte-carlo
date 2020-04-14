Pruned Monte-Carlo Simulations
========================

This code was forked from https://github.com/todo314/pruned-monte-carlo on 28th February 2020.

## Usage
Given a graph with edge probabilities, it selects a seed set of a given size, as well as providing other data

    $ make
    $ ./pmc_greed tsv_file target_seed_size number_of_random_graphs seed_delta
* tsv_file: input file (see below)
* target_seed_size: the target seed set size
* number_of_random_graphs: the number of random graphs to simulate (larger = more accurate)
* seed_delta: a fixed integer to be added as a seed so as to allow for different seeds

### Example

## Greedy algorithm program
    $ make
    $ ./pmc_greed samples/sample.tsv 5 100000 0
    0       1.12257 0.3489
    4       1.09755 0.391786
    2       1.00769 0.429225
    3       0.97071 0.465096
    1       0.80148 0.501

On each line,
* The first integer refers to the seed corresponding to input `.tsv`
* The second number refers to the marginal gain of that seed. Submodularity of the independent cascade model of influence means this number should only decrease.
* The third number is the amount of time in seconds used to calculate up to that seed. This number should only increase.

## Estimation program
    $ ./pmc_est samples/sample.tsv samples/sample_seeds.txt 100000 0
    0       1.12257
    4       1.09755
    2       1.00769
    3       0.97071
    1       0.80148

On each line,
* The first integer refers to the seed corresponding to the solution. The solution file can be space separated, tab-separated or newline separated integers. They should correspond to the `.tsv` files.
* The second number is the marginal gain of that seed. The program processes exactly the order as given. Different orders will result in different marginal gain numbers. In particular, the gain may not be submodular, but should be submodular if the same sequence resulting from a greedy algorithm is used.

## Format of the input graph:
    u_1	v_1	p_1
    ...
    u_i	v_i	p_i
    ...
    u_m	v_m	p_m
* The i-th line means an directed edge (u_i, v_i) with propagation probability p_i (see `samples/sample.tsv`).
* Vertices should be described by integers starting from zero.

## Changelog
### 14th April 2020

* Added timing functionality.
* Added seeding functionality.
* Removed verbosity of output.
* Minor changes:
  * Renamed items:
    * `samples/sample_graph.tsv` -> `samples/sample.tsv`
    * `samples/sample_graph_seeds.txt` -> `samples/sample_seeds.txt`
    *  `src/inf_est.cpp` -> `src/est.cpp`
  * Added new flags to Makefile.
  * Changed certain variables to unsigned to comply with compiler requirements.
  * Removed all instances of `using`.
  * Added `.gitignore` for outputs of `make`.

### 28th February 2020

* Renamed resulting executable as `pmc_greed`.
* Changed `pmc_greed` to also provide marginal gain estimates. Example output:
  ```
  $ ./pmc_greed samples/sample_graph.tsv 5 200
  0-th seed and marginal gain =   4       1.155
  1-th seed and marginal gain =   0       1.11
  2-th seed and marginal gain =   2       1.005
  3-th seed and marginal gain =   3       0.935
  4-th seed and marginal gain =   1       0.795
  ```
  This is expected output as the marginal gains are decreasing as the influence function is submodular under the independent cascade model.
* Added a new executable `pmc_est`. Essentially, given a seed set file which corresponds to the graph file, the `pmc_est` estimates the marginal gain of each seed. The text file `sample_graph_seeds.txt` shows how a possible input could be like. The input can also be newline delimited. Example usage:
  ```
  $ ./pmc_est samples/sample_graph.tsv samples/sample_graph_seeds.txt 200
  Marginal gain of seed 4 =       1.155
  Marginal gain of seed 0 =       1.11
  Marginal gain of seed 2 =       1.005
  Marginal gain of seed 3 =       0.935
  Marginal gain of seed 1 =       0.795
  ```
  The output agrees with the above as it essentially uses the same setup code and skips the greedy portion.
* Changed `pmc.hpp` to not use `using namespace std;`, [following common convention](https://stackoverflow.com/questions/14575799/using-namespace-std-in-a-header-file).
* All other instances of `using namespace std;` have been changed to using specific things within `std`.

## Original Paper

* Naoto Ohsaka, Takuya Akiba, Yuichi Yoshida, and Ken-ichi Kawarabayashi. **[Fast and Accurate Influence Maximization on Large Networks with Pruned Monte-Carlo Simulations](http://www.aaai.org/ocs/index.php/AAAI/AAAI14/paper/view/8455)**.
In AAAI-14, pages 138--144, 2014.

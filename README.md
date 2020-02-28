Pruned Monte-Carlo Simulations
========================

This code was forked from https://github.com/todo314/pruned-monte-carlo on 28th February 2020.
## Changes from original repository
Note that I am only a novice at C++. I am aware that there is code repetition for the setup for the algorithm in `pmc.cpp`.

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


# Original Readme Below

This is a fast and accurate algorithm for the influence maximization problem under the independent cascade model.

## Usage
Given a graph with edge probabilities, it selects a seed set of a given size.

    $ make
    $ ./benchmark graph k R
* graph: input file (see below)
* k: the seed set size
* R: the number of random graphs (larger = more accurate)

### Example

    $ make
    $ ./benchmark ./sample_graph.tsv 5 200
    0-th seed =     4
    1-th seed =     0
    2-th seed =     2
    3-th seed =     3
    4-th seed =     1

### Format of the input graph:
    u_1	v_1	p_1
    ...
    u_i	v_i	p_i
    ...
    u_m	v_m	p_m
* The i-th line means an directed edge (u_i, v_i) with propagation probability p_i (see `sample_graph.tsv`).
* Vertices should be described by integers starting from zero.

## References

* Naoto Ohsaka, Takuya Akiba, Yuichi Yoshida, and Ken-ichi Kawarabayashi. **[Fast and Accurate Influence Maximization on Large Networks with Pruned Monte-Carlo Simulations](http://www.aaai.org/ocs/index.php/AAAI/AAAI14/paper/view/8455/8411)**.
In AAAI-14, pages 138--144, 2014.

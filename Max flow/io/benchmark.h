#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "../data structures/graph.h"

/**
 * @brief Starts each algorithm on the given network and measures the elapsed time of
          execution of each algorithm.
 * 
 * @tparam T Flow type.
 * @param graph The residual network to test.
 * @param num_of_runs The number of runs per algorithm.
 */
 // add return for results?
template <typename T>
void start(ds::Graph<T>& graph, int num_of_runs=1);

/**
 * @brief Function to benchmark a max flow algorithm given by the function pointer.
 * 
 * @tparam T Flow type.
 * @param graph The residual network.
 * @param mf_algorithm Function pointer to the algorithm we want to time.
 * @return auto pair of (elapsed_time [ms], computed max flow)
 */
template <typename T>
auto benchmark(ds::Graph<T>& graph, T (* mf_algorithm) (ds::Graph<T>& graph));

template <typename T>
void printResult(T result_max_flow, auto result_time, std::string_view algorithm_used, int num_of_runs=1);

#include "benchmark.ipp"

#endif
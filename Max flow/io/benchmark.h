#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "../data structures/graph.h"

/**
 * @brief Starts each algorithm on the given network and measures the elapsed time of
          execution of each algorithm.
 * 
 * @tparam flow_t Flow type.
 * @param graph The residual network to test.
 * @param num_of_runs The number of runs per algorithm.
 */
 // add return for results?
template <typename flow_t>
void start(ds::Graph<flow_t>& graph, int num_of_runs=1);

/**
 * @brief Function to benchmark a max flow algorithm given by the function pointer.
 * 
 * @tparam flow_t Flow type.
 * @param graph The residual network.
 * @param mf_algorithm Function pointer to the algorithm we want to time.
 * @return auto pair of (elapsed_time [ms], computed max flow)
 */
template <typename flow_t>
auto benchmark(ds::Graph<flow_t>& graph, flow_t (* mf_algorithm) (ds::Graph<flow_t>& graph));

template <typename flow_t>
void printResult(flow_t result_max_flow, auto result_time, std::string_view algorithm_used, int num_of_runs=1);

#include "benchmark.ipp"

#endif
#ifndef BENCHMARK_IPP
#define BENCHMARK_IPP

#include "../data structures/graph.h"

#include <chrono>


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
void start(ds::Graph<T>& graph, int num_of_runs) { 
    using mf_algorithm = T (*) (ds::Graph<T>& graph);

    num_of_runs = std::max(num_of_runs, 1);
    std::map<std::string, mf_algorithm> to_check = {
       {"FORD-FULKERSON DFS"                , &algorithms::ford_fulkerson},
       {"EDMONDS-KARP"                      , &algorithms::edmonds_karp},
       {"DINIC'S"                           , &algorithms::dinic},
       {"PUSH-RELABEL"                      , &algorithms::push_relabel},
       {"HIGHEST LABEL PUSH RELABEL + GAP"  , &algorithms::hi_push_relabel}
    };

    std::chrono::microseconds::rep elapsed_time{};
    T max_flow{0};
    // remember max flow values computed and their average times
    //std::map<std::string, T> max_flows{};
    for(auto const& algorithm : to_check) {
        for(int i{0}; i < num_of_runs; ++i) {
            // TODO: generate new graph with the same number of nodes and edges in each run
            auto result{benchmark(graph, algorithm.second)};
            graph.restore();
            elapsed_time += result.first;
            max_flow = result.second;
        }
        printResult(max_flow, elapsed_time, algorithm.first, num_of_runs);
        elapsed_time = 0;
        max_flow = 0;
    }
}

/**
 * @brief Function to benchmark a max flow algorithm given by the function pointer.
 * 
 * @tparam T Flow type.
 * @param graph The residual network.
 * @param mf_algorithm Function pointer to the algorithm we want to time.
 * @return auto pair of (elapsed_time [ms], computed max flow)
 */
template <typename T>
auto benchmark(ds::Graph<T>& graph, T (* mf_algorithm) (ds::Graph<T>& graph)) {
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    start = std::chrono::steady_clock::now();
    T max_flow{mf_algorithm(graph)};
    end = std::chrono::steady_clock::now();

    std::chrono::microseconds::rep elapsed_time{std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()};
    return std::pair{elapsed_time, max_flow};
}

template <typename T>
void printResult(T result_max_flow, auto result_time, std::string_view algorithm_used, int num_of_runs) {
    std::cout << "\n--------------------------------------------------------\n\n";
    std::cout << algorithm_used << ":\n";
    std::string edges_visited{};
    if(algorithm_used == "FORD-FULKERSON DFS") {edges_visited = std::to_string(C::ff_edges_visited);}
    else if(algorithm_used == "EDMONDS-KARP") {edges_visited = std::to_string(C::ek_edges_visited);}
    else if(algorithm_used == "DINIC'S") {edges_visited = std::to_string(C::dinic_edges_visited);}
    if(edges_visited != "") {
        std::cout << "Total number of edges checked during computation: " << edges_visited << "\n";
    }
    std::cout << "Max flow: " << result_max_flow << " in an average of " << result_time*1.0/num_of_runs << 
        " ms over " << num_of_runs << " run" << ((num_of_runs > 1)?"s.\n" : ".\n");
}

#endif
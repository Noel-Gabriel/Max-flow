#include "data structures/graph.h"
#include "algorithms/fordfulkerson.h"
#include "algorithms/edmondskarp.h"
#include "algorithms/dinic.h"
#include "algorithms/pushrelabel.h"
#include "algorithms/hipushrelabel.h"
#include "algorithms/counter.h"
#include "io/graphreader.h"
#include "PushRelabel.h"

#include <iostream>
#include <chrono>
#include <cassert>


template <typename flow_t>
using Graph = ds::Graph<flow_t>;

/**
 * @brief Function to benchmark a max flow algorithm given by the function pointer.
 * 
 * @tparam flow_t Flow type.
 * @param graph The residual network.
 * @param mf_algorithm Function pointer to the algorithm we want to time.
 * @return auto pair of (elapsed_time [ms], computed max flow)
 */
template <typename flow_t>
auto benchmark(Graph<flow_t>& graph, flow_t (* mf_algorithm) (Graph<flow_t>& graph)) {
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    start = std::chrono::steady_clock::now();
    flow_t max_flow{mf_algorithm(graph)};
    end = std::chrono::steady_clock::now();

    std::chrono::microseconds::rep elapsed_time{std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()};
    return std::pair{elapsed_time, max_flow};
}

bool check(auto& graph) {
    for(int i{0}; i < graph.m_adj_list.size(); ++i) {
        for(int j{0}; j < graph.m_adj_list[i].size(); ++j) {
            auto* edge{graph.m_adj_list[i][j]};
            if(edge->reverse->reverse != edge) {
                std::cout << edge->tail << " " << edge->head << "\n";
                std::cout << edge->reverse->reverse->tail << " " << edge->reverse->reverse->head << "\n";
                return false;
            }
        }
    }
    return true;
}

int main() {
    Graph<int> g = io::load_graph_from_file("/Users/noel/Desktop/Max flow vscode/Max-flow/Max flow/test.dimacs");

    PushRelabel hpr = io::load_pr("/Users/noel/Desktop/Max flow vscode/Max-flow/Max flow/test.dimacs");

    /*
    Graph<int> g{8};
    g.add_edge(0, 1, 2);

    g.add_edge(0, 2, 4);
    g.add_edge(1, 2, 3);
    g.add_edge(1, 3, 1);
    g.add_edge(2, 3, 8);
    g.add_edge(3, 7, 8);
    g.add_edge(3, 5, 9);
    g.add_edge(5, 6, 10);*/
/*
    PushRelabel hpr(8);
    hpr.addEdge(0, 1, 2);
    hpr.addEdge(0, 2, 4);
    hpr.addEdge(1, 2, 3);
    hpr.addEdge(1, 3, 1);
    hpr.addEdge(2, 3, 8);
    hpr.addEdge(3, 7, 8);
    hpr.addEdge(3, 5, 9);
    hpr.addEdge(5, 6, 10);
*/
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    long long max_flow_hipr = hpr.calc(0, g.m_t);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //hpr.printLabels();
    
    std::cout << "HIPR:\n";
    std::cout << "Max flow: " << max_flow_hipr << " in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms.\n";

    std::cout << "------------------------------\n";
    std::cout << "FORD-FULKERSON DFS:\n";
    auto ff{benchmark(g, &algorithms::ford_fulkerson)};
    std::cout << "Total number of edges checked during computation: " << C::ff_edges_visited << "\n";
    std::cout << "Max flow: " << ff.second << " in " << ff.first << " ms.\n";
    g.restore();

    std::cout << "-----------------------------\n";
    std::cout << "EDMONDS-KARP:\n";
    auto ek{benchmark(g, &algorithms::edmonds_karp)};
    std::cout << "Total number of edges checked during computation: " << C::ek_edges_visited << "\n";
    std::cout << "Max flow: " << ek.second << " in " << ek.first << " ms.\n";
    g.restore();
    

    assert(ek.second == ff.second && "Ford-Fulkerson and Edmonds-Karp max flow value not equal");

    std::cout << "-----------------------------\n";
    std::cout << "DINIC:\n";
    auto dinic{benchmark(g, &algorithms::dinic)};
    std::cout << "Total number of edges checked during computation: " << C::dinic_edges_visited << "\n";
    std::cout << "Max flow: " << dinic.second << " in " << dinic.first << " ms.\n";
    g.restore();

    assert(ek.second == dinic.second && "FF/EK and Dinic's max flow value not equal");
    
    // Generic push relabel VERY SLOW wtf
    if(g.m_n < 5000) {
        std::cout << "-----------------------------\n";
        std::cout << "PUSH RELABEL\n";
        auto pr{benchmark(g, &algorithms::push_relabel)};
        std::cout << "Max flow: " << pr.second << " in " << pr.first << " ms.\n";
        g.restore();

        assert(ek.second == pr.second && "FF/EK/Dinic and Push-Relabel max flow value not equal");
    }

    std::cout << "-------------------------------\n";
    std::cout << "HIGHEST LABEL PUSH RELABEL + GAP\n";
    auto hi_pr{benchmark(g, &algorithms::hi_push_relabel)};
    std::cout << "Max flow: " << hi_pr.second << " in " << hi_pr.first << " ms.\n";
    g.restore();

    assert(ek.second == hi_pr.second && "FF/EK/Dinic/PR and High Push-Relabel max flow value not equal");

    return 0;
}

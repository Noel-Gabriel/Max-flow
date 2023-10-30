#include "data structures/graph.h"
#include "algorithms/fordfulkerson.h"
#include "algorithms/edmondskarp.h"
#include "algorithms/dinic.h"
#include "algorithms/pushrelabel.h"
#include "io/graphreader.h"
#include "algorithms/counter.h"

#include <iostream>

template <typename flow_t>
using Graph = data_structures::Graph<flow_t>;

int main() {
    //Graph<int> g = io::load_graph_from_file("/Users/noel/Desktop/git/Uni/Max flow/test.dimacs");

    
    Graph<int> g{4};
    g.add_edge(0, 1, 2);
    g.add_edge(0, 2, 4);
    g.add_edge(1, 3, 1);
    g.add_edge(2, 3, 5);
    g.add_edge(1, 2, 3);
    
    g.save();
    std::cout << "DFS:\n";
    int max_flow = algorithms::ford_fulkerson(g);
    std::cout << "Total number of edges checked during computation: " << C::ff_edges_visited << "\n";
    std::cout << "Max flow: " << max_flow << "\n";
    g.restore();
    std::cout << "-----------------------------\n";
    std::cout << "BFS:\n";
    int max_flow_ek = algorithms::edmonds_karp(g);
    std::cout << "Total number of edges checked during computation: " << C::ek_edges_visited << "\n";
    std::cout << "Max flow: " << max_flow_ek << "\n";
    g.restore();
    std::cout << "-----------------------------\n";
    std::cout << "DINIC:\n";
    int max_flow_dinic = algorithms::dinic(g);
    std::cout << "Total number of edges checked during computation: " << C::dinic_edges_visited << "\n";
    std::cout << "Max flow: " << max_flow_dinic << "\n";
    g.restore();
    std::cout << "-----------------------------\n";
    std::cout << "PUSH RELABEL\n";
    int max_flow_pr = algorithms::push_relabel(g);
    std::cout << "Max flow: " << max_flow_pr << "\n";
    g.restore();
    return 0;
}

#ifndef EDMONDS_KARP_IPP
#define EDMONDS_KARP_IPP

#include "fordfulkerson.ipp"
#include "../data structures/graph.h"
#include <queue>
#include <map>

namespace algorithms {

    /**
     * @brief Bfs used by ford-fulkerson.
     * 
     *
     * @tparam T Flow type.
     * @param graph The residual network. 
     * @param augmenting_path Container to save the path from s to t if one is found.
     * @return The maximum flow that can be pushed on the path found.
     */
    template <typename T>
    T ff_bfs(const ds::Graph<T>& graph, auto& augmenting_path) {
        // queue containing (vertex, flow pushed so far) pairs
        std::queue<std::pair<int, T>> to_visit{};
        // "infinite" flow to start the bfs
        to_visit.emplace(graph.m_s, std::numeric_limits<T>::max());

        while(!to_visit.empty()) {
            auto current_vertex{to_visit.front()}; // (vertex, flow) pair
            to_visit.pop();
            for(auto* edge : graph.m_adj_list[current_vertex.first]) {
                // counter for comparison, irrelevant to the search
                ++C::ek_edges_visited;
                if(augmenting_path[edge->head] || edge->capacity <= 0) {
                    continue;
                }
                T new_flow_pushed{std::min(current_vertex.second, edge->capacity)};
                // remember current edge
                augmenting_path[edge->head] = edge;
                if(edge->head == graph.m_t) {
                    return new_flow_pushed;
                }
                to_visit.emplace(edge->head, new_flow_pushed);
            }
        }
        // no s-t path
        return 0;
    }

    /**
     * @brief Computes the maximum flow of the given graph using 
     *        the ford-fulkerson method and a breath-first search 
     *        to find augmenting paths.
     * 
     * @tparam T Flow type.
     * @param graph The residual network.
     * @return T The value of a maximum flow.
     */
    template <typename T>
    T edmonds_karp(ds::Graph<T>& graph) {
        return _ford_fulkerson(graph, &ff_bfs);
    }

}

#endif

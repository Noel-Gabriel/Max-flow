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
     * @tparam flow_t Flow type.
     * @param graph The residual network. 
     * @param augmenting_path Container to save the path from s to t if one is found.
     * @return The maximum flow that can be pushed on the path found.
     */
    template <typename flow_t>
    flow_t ff_bfs(const auto& graph, std::vector<int>& augmenting_path) {
        // queue for the bfs containing (vertex, pushed flow) pairs
        std::queue<std::pair<int, flow_t>> to_visit{};
        // "infinite" flow to start the bfs
        to_visit.emplace(graph.m_s, std::numeric_limits<flow_t>::max());

        while(!to_visit.empty()) {
            auto current_vertex{to_visit.front()}; // (vertex, flow) pair
            to_visit.pop();
            for(auto adj : graph.m_adj_list[current_vertex.first]) {
                ++C::ek_edges_visited;
                auto& edge = graph.m_edges[adj]; // type Edge
                // next vertex has already been visited or this edge is saturated
                if(augmenting_path[edge.head] != -1 || edge.capacity <= 0) {
                    continue;
                }
                // maximum possible flow that can be pushed through this edge
                flow_t new_flow_pushed{std::min(current_vertex.second, edge.capacity)};
                // remember current edge
                augmenting_path[edge.head] = adj;
                if(edge.head == graph.m_t) {
                    return new_flow_pushed;
                }
                to_visit.emplace(edge.head, new_flow_pushed);
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
     * @tparam flow_t Flow type.
     * @param graph The residual network.
     * @return flow_t The maximum flow.
     */
    template <typename flow_t>
    flow_t edmonds_karp(data_structures::Graph<flow_t>& graph) {
        return _ford_fulkerson(graph, &ff_bfs);
    }

}

#endif

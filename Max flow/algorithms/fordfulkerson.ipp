#ifndef FORD_FULKERSON_IPP
#define FORD_FULKERSON_IPP

#include "../data structures/graph.h"
#include "counter.h"
#include <stack>
#include <map>

namespace algorithms {

    /**
     * @brief Dfs used by ford-fulkerson.
     * 
     *
     * @tparam T Flow type.
     * @param graph The residual network. 
     * @param augmenting_path Container to save the path from s to t if one is found.
     * @return The maximum flow that can be pushed on the path found.
     */
    template <typename T>
    T ff_dfs(const ds::Graph<T>& graph, auto& augmenting_path) {
        // stack containing (vertex, flow pushed so far) pairs
        std::stack<std::pair<int, T>> to_visit{};
        // "infinite" flow from s to start the dfs
        to_visit.emplace(graph.m_s, std::numeric_limits<T>::max());

        while(!to_visit.empty()) {
            auto current_vertex{to_visit.top()}; // (vertex, flow) pair
            to_visit.pop();
            for(auto* edge : graph.m_adj_list[current_vertex.first]) {
                // counter for comparison, irrelevant to the search
                ++C::ff_edges_visited;
                if(augmenting_path[edge->head] || edge->capacity <= 0) {
                    continue;
                }
                T new_flow_pushed{std::min(current_vertex.second, edge->capacity)};
                // remember the current edge
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
     * @brief Main ford-fulkerson "method". Used by ford-fulkerson with 
     *        a dfs, and by edmonds-karp with a bfs.
     * 
     *
     * @tparam T Flow type.
     * @param graph The residual network.
     * @param search The search function to be used to find augmenting paths.
     * @return The value of a maximum flow.
     */
    template <typename T>
    T _ford_fulkerson(ds::Graph<T>& graph, 
            T (* search) (const ds::Graph<T>& graph, 
                std::vector<typename ds::Graph<T>::Edge*>& augmenting_path)) {
        // to store the augmenting path
        std::vector<typename ds::Graph<T>::Edge*> augmenting_path(graph.m_n, nullptr);
        T max_flow{0};
        // flow pushed by the next augmenting path
        T flow_pushed{0};
        // find augmenting path using the given search function
        while((flow_pushed = search(graph, augmenting_path))) {
            int v{graph.m_t};
            // update capacities
            while(v != graph.m_s) {
                auto* edge = augmenting_path[v];
                edge->capacity -= flow_pushed;
                edge->reverse->capacity += flow_pushed;
                v = edge->tail;
            }
            max_flow += flow_pushed;
            // clear current augmenting path for the next one
            std::fill(augmenting_path.begin(), augmenting_path.end(), nullptr);
        }
        return max_flow;
    }

    /**
     * @brief Computes the maximum flow of the given graph using 
     *        the ford-fulkerson method and a depth-first search 
     *        to find augmenting paths.
     * 
     * @tparam T Flow type.
     * @param graph The residual network.
     * @return T The value of a maximum flow.
     */
    template <typename T> 
    T ford_fulkerson(ds::Graph<T>& graph) {
        return _ford_fulkerson<T>(graph, &ff_dfs);
    }
}

#endif
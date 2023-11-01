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
     * @tparam flow_t Flow type.
     * @param graph The residual network. 
     * @param augmenting_path Container to save the path from s to t if one is found.
     * @return The maximum flow that can be pushed on the path found.
     */
    template <typename flow_t>
    flow_t ff_dfs(const ds::Graph<flow_t>& graph, auto& augmenting_path) {
        // stack for the dfs containing (vertex, pushed flow) pairs
        std::stack<std::pair<int, flow_t>> to_visit{};
        // "infinite" flow from s to start the dfs
        to_visit.emplace(graph.m_s, std::numeric_limits<flow_t>::max());

        while(!to_visit.empty()) {
            auto current_vertex{to_visit.top()}; // (vertex, flow) pair
            to_visit.pop();
            for(auto* edge : graph.m_adj_list[current_vertex.first]) {
                ++C::ff_edges_visited;
                // next vertex has already been visited or this edge is saturated
                if(augmenting_path[edge->head] || edge->capacity <= 0) {
                    continue;
                }
                // maximum possible flow that can be pushed through this edge
                flow_t new_flow_pushed{std::min(current_vertex.second, edge->capacity)};
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
     * @tparam flow_t Flow type.
     * @param graph The residual network to compute the maximum flow.
     * @param search The search function to be used to find augmenting paths.
     * @return The maximum flow of the given network.
     */
    template <typename flow_t>
    flow_t _ford_fulkerson(ds::Graph<flow_t>& graph, 
            flow_t (* search) (const ds::Graph<flow_t>& graph, 
                std::vector<typename ds::Graph<flow_t>::Edge*>& augmenting_path)) {
        // to save the augmenting path found by the given search function
        std::vector<typename ds::Graph<flow_t>::Edge*> augmenting_path(graph.m_n, nullptr);
        // current total flow pushed
        flow_t max_flow{0};
        // flow pushed by the next augmenting path
        flow_t flow_pushed{0};
        // find augmenting path using the given search function
        while((flow_pushed = search(graph, augmenting_path))) {
            int v{graph.m_t};
            // update capacities
            while(v != graph.m_s) {
                auto* edge = augmenting_path[v];
                //std::cout << v << " <- ";
                edge->capacity -= flow_pushed;
                // the reversed edge is next to the non reversed edge, can use xor to index it
                edge->reverse->capacity += flow_pushed;
                v = edge->tail;
            }
            //std::cout << "0 " << "     flow  pushed: " << flow_pushed << "\n";
            // increase total flow using the augmenting path found
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
     * @tparam flow_t Flow type.
     * @param graph The residual network.
     * @return flow_t The maximum flow.
     */
    template <typename flow_t> 
    flow_t ford_fulkerson(ds::Graph<flow_t>& graph) {
        return _ford_fulkerson<flow_t>(graph, &ff_dfs);
    }
}

#endif
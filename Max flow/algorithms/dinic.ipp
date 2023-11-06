#ifndef DINIC_IPP
#define DINIC_IPP

#include "../data structures/graph.h"
#include "counter.h"
#include <iostream>
#include <vector>
#include <queue>

namespace algorithms {

    /**
     * @brief Assigns each vertex in the graph a level, where the level is the
     *        number of edges on the shortest path from s to the vertex.
     * 
     * @tparam T Flow type.
     * @param graph The residual network. 
     * @return A vector (container) where each vertex indexes its level in the graph.
     */
    template <typename T>
    std::vector<int> build_level_graph(const ds::Graph<T>& graph) {
        std::vector<int> level(graph.m_n, -1);
        level[graph.m_s] = 0;
        std::queue<int> to_visit{};
        to_visit.push(graph.m_s);
        while(!to_visit.empty()) {
            int vertex{to_visit.front()};
            to_visit.pop();
            for(auto* edge : graph.m_adj_list[vertex]) {
                // counter for comparison, irrelevant to dinic's
                ++C::dinic_edges_visited;
                if(edge->capacity <= 0 || level[edge->head] != -1) {
                    continue;
                }
                level[edge->head] = level[vertex]+1;
                to_visit.push(edge->head);
            }
        }
        return level;
    }

    /**
     * @brief Uses a depth-first search to find an augmenting path in the
     *        current layered network.
     * 
     *
     * @tparam T Flow type.
     * @param graph The residual network.
     * @param vertex The current vertex visited by the search.
     * @param flow_pushed The flow pushed to this vertex so far.
     * @param level The current level of each vertex in the residual network.
     * @param edges_to_visit The edges that the current dfs needs to consider.
     * @return The flow pushed on the augmenting path found.
     */
    template <typename T>
    T dinic_dfs(auto& graph, int vertex, T flow_pushed, std::vector<int>& level, std::vector<int>& edges_to_visit) {
        if(graph.m_t == vertex) { 
            return flow_pushed; 
        }
        for(int& i{edges_to_visit[vertex]}; i < graph.m_adj_list[vertex].size(); ++i) {
            // counter for comparison, irrelevant to dinic's
            ++C::dinic_edges_visited;
            auto* edge{graph.m_adj_list[vertex][i]};
            if(level[edge->head] - 1 != level[vertex] || edge->capacity <= 0) {
                continue;
            }
            T push{dinic_dfs(graph, edge->head, std::min(flow_pushed, edge->capacity), level, edges_to_visit)};
            // no s-t path using this edge
            if(push == 0) {
                continue;
            }
            edge->capacity -= push;
            // update reverse edge denoting total flow pushed through this edge
            edge->reverse->capacity += push;
            return push;
        }
        // no s-t path using this vertex
        return 0;
    }

    /**
     * @brief Computes the maximum flow of the given graph using 
     *        Dinic's algorithm.
     * 
     * @tparam T Flow type.
     * @param graph The residual network.
     * @return T The value of a maximum flow.
     */
    template <typename T>
    T dinic(ds::Graph<T>& graph) {
        T max_flow{0};
        T flow_pushed{0};
        std::vector<int> level = build_level_graph(graph);
        // stores the next edge that can be considered during the next dfs on the current level graph
        std::vector<int> edges_to_visit(graph.m_n, 0);
        while(level[graph.m_t] != -1) {
            // push until a blocking flow is found
            while((flow_pushed = dinic_dfs<T>(graph, graph.m_s, std::numeric_limits<T>::max(), level, edges_to_visit))) {
                max_flow += flow_pushed;
            }
            // next level graph, considering all edges in the dfs again
            level = build_level_graph(graph);
            std::fill(edges_to_visit.begin(), edges_to_visit.end(), 0);
        }
        return max_flow;
    }
}

#endif
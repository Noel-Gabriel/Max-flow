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
     * @tparam flow_t Flow type.
     * @param graph The residual network 
     * @return A vector (container) where each vertex indexes its level in the graph.
     */
    template <typename flow_t>
    std::vector<int> build_level_graph(const ds::Graph<flow_t>& graph) {
        std::vector<int> level(graph.m_n, -1);
        level[graph.m_s] = 0;
        std::queue<int> to_visit{};
        to_visit.push(graph.m_s);
        while(!to_visit.empty()) {
            int vertex{to_visit.front()};
            to_visit.pop();
            for(auto* edge : graph.m_adj_list[vertex]) {
                ++C::dinic_edges_visited;
                // edge can't push any more flow or next vertex has been visited already
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
     * @tparam flow_t Flow type.
     * @param graph The residual network.
     * @param vertex The current vertex visited by the search.
     * @param flow_pushed The flow pushed to this vertex so far.
     * @param level The current level of each vertex in the residual network.
     * @param edges_to_visit The edges that the current dfs needs to consider.
     * @return The flow pushed on the augmenting path found.
     */
    template <typename flow_t>
    flow_t dinic_dfs(auto& graph, int vertex, flow_t flow_pushed, std::vector<int>& level, std::vector<int>& edges_to_visit) {
        // reached the sink
        if(graph.m_t == vertex) { 
            //std::cout << graph.m_t << " <- ";
            return flow_pushed; 
        }
        // only consider edges of each vertex which have not been visited by previous dfs' in the current level graph
        for(int& i{edges_to_visit[vertex]}; i < graph.m_adj_list[vertex].size(); ++i) {
            ++C::dinic_edges_visited;
            auto* edge{graph.m_adj_list[vertex][i]};
            // edge not part of a shortest path to t or is already saturated
            if(level[edge->head] - 1 != level[vertex] || edge->capacity <= 0) {
                continue;
            }
            // possible flow that can be pushed using this edge on the path to t
            flow_t push{dinic_dfs(graph, edge->head, std::min(flow_pushed, edge->capacity), level, edges_to_visit)};
            // no s-t path using this edge
            if(push == 0) {
                continue;
            }
            //std::cout << vertex << ((vertex == graph.m_s)? "": " <- ");
            // push through this edge
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
     * @tparam flow_t Flow type.
     * @param graph The residual network.
     * @return flow_t The maximum flow.
     */
    template <typename flow_t>
    flow_t dinic(ds::Graph<flow_t>& graph) {
        // total maximum flow pushed.
        flow_t max_flow{0};
        // flow pushed at each dfs
        flow_t flow_pushed{0};
        // stores the level or rank of each vertex
        std::vector<int> level = build_level_graph(graph);
        // stores the next edge that can be considered during the next dfs on the current level graph
        // this is where dinic's is more efficient than ford-fulkerson
        std::vector<int> edges_to_visit(graph.m_n, 0);
        // while s-t path exists
        while(level[graph.m_t] != -1) {
            //std::cout << "LEVEL: " << level[graph.m_t] << "\n";
            // push until a blocking flow is found
            while((flow_pushed = dinic_dfs<flow_t>(graph, graph.m_s, std::numeric_limits<flow_t>::max(), level, edges_to_visit))) {
                //std::cout << "        flow pushed: " << flow_pushed << "\n";
                max_flow += flow_pushed;
            }
            // build new level graph and consider all edges again
            level = build_level_graph(graph);
            std::fill(edges_to_visit.begin(), edges_to_visit.end(), 0);
        }
        return max_flow;
    }
}

#endif
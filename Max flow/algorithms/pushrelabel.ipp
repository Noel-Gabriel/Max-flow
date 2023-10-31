#ifndef PUSH_RELABEL_IPP
#define PUSH_RELABEL_IPP

#include "../data structures/graph.h"
#include "dinic.h" // for the build_level_graph function to initialize labels

#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

using namespace std::chrono;

namespace algorithms {
    /**
     * @brief Initializes the labels for the push-relabel algorithm.
     *
     *        The label for a vertex v is initialized as the shortest 
     *        v-t distance. labels[s] = #vertices, labels[t] = 0
     * 
     *
     * @tparam flow_t Flow type.
     * @param graph The residual network.
     * @return The (best) first valid label.
     */

    template <typename flow_t>
    std::vector<int> initialize_labels(data_structures::Graph<flow_t>& graph) {
        std::size_t n{graph.m_adj_list.size()}; // number of vertices
        std::vector<int> labels(n);
        // get shortest s-v distance, shortest v-t distance is then 
        // s-t distance minus s-v distance
        std::vector<int> level = build_level_graph(graph);
        int max_distance{level[graph.m_t]};
        for(int i{0}; i < n; ++i) {
            if(level[i] == -1) {
                labels[i] = 0; 
                continue;
            }
            labels[i] = std::max(max_distance-level[i], 0);
        }
        labels[graph.m_s] = n;
        return labels;
    }


    /**
     * @brief Performs the push operation in the push-relabel algorithm.
     * 
     *
     * @tparam flow_t Flow type.
     * @param graph The residual network.
     * @param excess The current excess flow for each vertex.
     * @param vertex The vertex we want to push from.
     * @param edge The edge used for pushing.
     */
    template <typename flow_t>
    bool push(std::vector<flow_t>& excess, auto& edge, auto& reverse_edge) {
        flow_t to_push = std::min(excess[edge.tail], edge.capacity);
        // update excess
        excess[edge.tail] -= to_push;
        excess[edge.head] += to_push;
        //std::cout << "PUSHED FROM " << vertex << " TO " <<graph.m_edges[edge].head << " TOTAL OF " << to_push << " UNITS\n";
        // push
        edge.capacity -= to_push;
        reverse_edge.capacity += to_push;
        // only add the first time node is activated.
        return to_push && to_push == excess[edge.head];
    }

    /**
     * @brief Initializes the preflow for the push-relabel algorithm.
     * 
     *        Sends as much flow es possible from every outgoing edge of s.
     * 
     *
     * @tparam flow_t Flow type.
     * @param graph The residual network.
     * @param excess The sum of ingoing flow for every vertex. (negativ for outgoing flow)
     * @param active Queue for active vertices.
     */
    template <typename flow_t>
    void initialize_preflow(data_structures::Graph<flow_t>& graph, std::vector<flow_t>& excess, std::queue<int>& active) {
        for(int edge_index : graph.m_adj_list[graph.m_s]) {
            // saturate each outgoing edge from s
            auto& edge{graph.m_edges[edge_index]};
            if(push(excess, edge, graph.m_edges[edge_index^1])) {
                active.push(edge.head);
            }
        }
    }

    /**
     * @brief Finds the new label for a given vertex.
     * 
     *        The new label is the minimal label of all adjacent vertices + 1
     * 
     * @tparam flow_t Flow type.
     * @param graph The residual network.
     * @param vertex Vertex we want the new lavel of.
     * @param labels Current labeling.
     * @return The new label value for vertex.
     */
    template <typename flow_t>
    int relabel(data_structures::Graph<flow_t>& graph, int vertex, std::vector<int>& labels) {
        int min_label{INT_MAX};
        int edge_index{0};
        //std::cout << "current label: " << labels[vertex] << ", relabeling to ";
        for(int i{0}; i < graph.m_adj_list[vertex].size(); ++i) {
            auto& edge = graph.m_edges[graph.m_adj_list[vertex][i]];
            if(edge.capacity > 0) {
                if(labels[edge.head] < min_label) {
                    min_label = labels[edge.head];
                    edge_index = i;
                }
            }
        }
        if(min_label < INT_MAX) {
            labels[vertex] = min_label+1;
        }
        return edge_index;
    }

    /**
     * @brief Computes the maximum flow in a given flow network using 
     *        Goldberg's and Tarjan's push-relabel algorithm.
     * 
     *
     * @tparam flow_t Flow type.
     * @param graph The residual network.
     * @return The maximum flow.
     */
    template <typename flow_t>
    flow_t push_relabel(data_structures::Graph<flow_t>& graph) {
        // initialization
        auto& adj_list{graph.m_adj_list};
        auto& edges{graph.m_edges};

        // labels
        //std::vector<int> labels{initialize_labels(graph)};
        std::vector<int> labels(adj_list.size(), 0);
        labels[graph.m_s] = adj_list.size();

        // "current-arc" data structure proposed by wikipedia
        std::vector<int> current_edges(adj_list.size(), 0);

        // excess flow of each vertex
        std::vector<flow_t> excess(adj_list.size(), 0);
        excess[graph.m_s] = std::numeric_limits<flow_t>::max();
        // queue of active vertices
        std::queue<int> active{};
        // initialize preflow
        initialize_preflow(graph, excess, active);

        // main push-relabel
        while(!active.empty()) {
            int vertex{active.front()};
            active.pop();
            if(vertex == graph.m_s || vertex == graph.m_t) { continue; }
            // discharge operation defined on wikipedia
            while(excess[vertex] > 0) {
                if(current_edges[vertex] == adj_list[vertex].size()) {
                    current_edges[vertex] = relabel(graph, vertex, labels);
                } else {
                    int edge_index{adj_list[vertex][current_edges[vertex]]};
                    auto& edge{edges[edge_index]};
                    if(edge.capacity > 0 && labels[vertex] > labels[edge.head]) {
                        if(push(excess, edge, edges[edge_index^1])) {
                            active.push(edge.head);
                        }
                    } else {
                        ++current_edges[vertex];
                    }
                }
            }
        }
        return excess[graph.m_t];
    }
}

#endif

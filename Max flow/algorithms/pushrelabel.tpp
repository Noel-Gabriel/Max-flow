#ifndef PUSH_RELABEL_TPP
#define PUSH_RELABEL_TPP

#include "../data structures/graph.h"
#include "dinic.h" // for the build_level_graph function to initialize labels

#include <iostream>
#include <vector>
#include <queue>

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
            labels[i] = max_distance-level[i];
        }
        labels[graph.m_s] = n;
        return labels;
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
    void initialize_preflow(data_structures::Graph<flow_t>& graph, std::vector<flow_t>& excess, std::queue<int>& active, std::vector<bool>& is_active) {
        for(int edge : graph.m_adj_list[graph.m_s]) {
            // saturate each outgoing edge from s
            flow_t preflow{graph.m_edges[edge].capacity};
            graph.m_edges[edge].capacity = 0;
            graph.m_edges[edge^1].capacity = preflow;
            // update excesses
            int adj{graph.m_edges[edge].head};
            excess[adj] += preflow;
            excess[graph.m_s] -= preflow;
            // add adjacent vertex of s as active
            if(adj != graph.m_t) {
                active.push(adj);
                is_active[adj] = true;
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
    int relabel(data_structures::Graph<flow_t>& graph, int vertex, std::vector<int>& labels, std::vector<int>& excess) {
        std::size_t min_label{graph.m_adj_list.size()};
        int edge_index{0};
        //std::cout << "current label: " << labels[vertex] << ", relabeling to ";
        for(int i{0}; i < graph.m_adj_list[vertex].size(); ++i) {
            int edge{graph.m_adj_list[vertex][i]};
            if(graph.m_edges[edge].capacity > 0) {
                if(labels[graph.m_edges[edge].head] < min_label) {
                    min_label = labels[graph.m_edges[edge].head];
                    edge_index = i;
                }
            }
        }
        labels[vertex] = min_label+1;
        //std::cout << labels[vertex] << "\n";
        return edge_index;
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
    void push(data_structures::Graph<flow_t>& graph, std::vector<flow_t>& excess, int vertex, int edge) {
        flow_t to_push = std::min(excess[vertex], graph.m_edges[edge].capacity);
        // update excesses 
        excess[vertex] -= to_push;
        excess[graph.m_edges[edge].head] += to_push;
        std::cout << "PUSHED FROM " << vertex << " TO " <<graph.m_edges[edge].head << " TOTAL OF " << to_push << " UNITS\n";
        // push
        graph.m_edges[edge].capacity -= to_push;
        graph.m_edges[edge^1].capacity += to_push;
    }

    template <typename flow_t>
    void discharge(data_structures::Graph<flow_t>& graph, std::vector<flow_t>& excess, int vertex, std::vector<int>& labels, std::vector<int>& current_edges, std::queue<int>& active, std::vector<bool>& is_active) {
        while(excess[vertex] > 0) {
            if(current_edges[vertex] >= graph.m_adj_list[vertex].size()) {
                current_edges[vertex] = relabel(graph, vertex, labels, excess);
            } else {
                int current_edge{graph.m_adj_list[vertex][current_edges[vertex]]};
                //std::cout << "Checking edge " << graph.m_edges[current_edge].tail << " - " << graph.m_edges[current_edge].tail << " -> " << graph.m_edges[current_edge].head << " tail label " << labels[graph.m_edges[current_edge].head] << "\n";
                if(graph.m_edges[current_edge].capacity > 0 && labels[vertex] == labels[graph.m_edges[current_edge].head]+1) {
                    push(graph, excess, vertex, current_edge);
                    if(!is_active[graph.m_edges[current_edge].head] && graph.m_edges[current_edge].head != graph.m_s && graph.m_edges[current_edge].head != graph.m_t) {
                        active.push(graph.m_edges[current_edge].head);
                        is_active[graph.m_edges[current_edge].head] = true;
                    }
                } else {
                    ++current_edges[vertex];
                }
            }
         }
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

        // labels
        std::vector<int> labels{initialize_labels(graph)};

        // "current-arc" data structure proposed by wikipedia
        std::vector<int> current_edges(graph.m_adj_list.size(), 0);

        // excess flow of each vertex
        std::vector<flow_t> excess(graph.m_adj_list.size(), 0);
        // queue of active vertices
        std::queue<int> active{};

        std::vector<bool> is_active(graph.m_adj_list.size(), false);

        // initialize preflow
        initialize_preflow(graph, excess, active, is_active);
        
        // main push-relabel
        while(!active.empty()) {
            int vertex{active.front()};
            active.pop();
            is_active[vertex] = false;
            // discharge operation defined in wikipedia
            discharge(graph, excess, vertex, labels, current_edges, active, is_active);
        }
        
        std::cout << "Lables:\n";
        for(auto l : labels) {
            std::cout << l << " ";
        }
        std::cout << "\n";
        std::cout << "excess:\n"; 
        for(auto e : excess) {
            std::cout << e << " ";
        }
        std::cout << "\n";
        
        return excess[graph.m_t];
    }
}

#endif

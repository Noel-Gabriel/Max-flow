#ifndef PUSH_RELABEL_IPP
#define PUSH_RELABEL_IPP

#include "../data structures/graph.h"
#include "counter.h"

#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

namespace algorithms {

    /**
     * @brief Performs the push operation in the push-relabel algorithm.
     * 
     *
     * @tparam T Flow type.
     * @param excess The sum of ingoing flow for every vertex. (negative for outgoing flow).
     * @param edge The edge used for pushing.
     * @return returns true if the node we pushed to got active after the push.
     */
    template <typename T>
    bool push(std::vector<T>& excess, auto* edge) {
        T to_push = std::min(excess[edge->tail], edge->capacity);
        // update excess
        excess[edge->tail] -= to_push;
        excess[edge->head] += to_push;
        // push
        edge->capacity -= to_push;
        edge->reverse->capacity += to_push;
        // only add to queue the first time node is activated.
        return to_push && to_push == excess[edge->head];
    }

    /**
     * @brief Initializes the preflow for the push-relabel algorithm.
     * 
     *        Sends as much flow es possible from every outgoing edge of the source.
     * 
     *
     * @tparam T Flow type.
     * @param graph The residual network.
     * @param excess The sum of ingoing flow for every vertex. (negative for outgoing flow)
     * @param active Queue of active vertices.
     */
    template <typename T>
    void initialize_preflow(ds::Graph<T>& graph, std::vector<T>& excess, std::queue<int>& active) {
        for(auto* edge : graph.m_adj_list[graph.m_s]) {
            // saturate each outgoing edge from s
            if(push(excess, edge)) {
                active.push(edge->head);
            }
        }
    }

    /**
     * @brief Assigns a new label to the given vertex.
     * 
     *        The new label is the minimal label of all adjacent vertices + 1
     * 
     * @tparam T Flow type.
     * @param graph The residual network.
     * @param vertex The vertex to relabel.
     * @param labels Current labeling.
     * @return The index of the edge used to find the minimal labeling (push operations can only start at this edge)
     */
    template <typename T>
    int relabel(ds::Graph<T>& graph, int vertex, std::vector<int>& labels) {
        int min_label{INT_MAX};
        int edge_index{0};
        for(int i{0}; i < graph.m_adj_list[vertex].size(); ++i) {
            auto* edge{graph.m_adj_list[vertex][i]};
            if(edge->capacity > 0) {
                if(labels[edge->head] < min_label) {
                    min_label = labels[edge->head];
                    edge_index = i;
                }
            }
        }
        labels[vertex] = min_label+1;
        return edge_index;
    }

    /**
     * @brief Computes the value of a maximum flow in the given graph using 
     *        Goldberg's and Tarjan's push-relabel algorithm.
     * 
     *
     * @tparam T Flow type.
     * @param graph The residual network.
     * @return The value of a maximum flow.
     */
    template <typename T>
    T push_relabel(ds::Graph<T>& graph) {
        // initialization
        auto& adj_list{graph.m_adj_list};


        // labels (or heights), all 0 except for the source at n (#vertices in the graph)
        std::vector<int> labels(graph.m_n, 0);
        labels[graph.m_s] = graph.m_n;

        // "current-arc" data structure proposed by wikipedia 
        //https://en.wikipedia.org/wiki/Push–relabel_maximum_flow_algorithm
        std::vector<int> current_edges(graph.m_n, 0);

        // excess function
        std::vector<T> excess(graph.m_n, 0);
        excess[graph.m_s] = std::numeric_limits<T>::max();

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
                // node still active, but reached end of edges -> relabel
                if(current_edges[vertex] == adj_list[vertex].size()) {
                    current_edges[vertex] = relabel(graph, vertex, labels);
                    ++counters::pr_relabels;
                } else {
                    auto* edge{adj_list[vertex][current_edges[vertex]]};
                    if(edge->capacity > 0 && labels[vertex] == labels[edge->head]+1) {
                        if(push(excess, edge)) {
                            active.push(edge->head);
                            ++counters::pr_pushes;
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

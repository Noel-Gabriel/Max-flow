#ifndef HI_PUSH_RELABEL_IPP
#define HI_PUSH_RELABEL_IPP

#include "../data structures/graph.h"
#include "pushrelabel.h"

#include <vector>
#include <queue>

namespace algorithms {

    /**
     * @brief Initializes the acitve buckets.
     * 
     * @tparam flow_t Flow type.
     * @param graph The residual network.
     * @param excess The excess at each vertex (inf for s, 0 every other vertex).
     * @param active The buckets.
     * @param labels The labels for each vertex.
     * @return int The highest label when initializing the buckets.
     */
    template <typename flow_t>
    int initialize_buckets(data_structures::Graph<flow_t>& graph, std::vector<flow_t>& excess, 
            std::vector<std::vector<int>>& active, const std::vector<int>& labels) {
        int highest{-1};
        for(int edge_index : graph.m_adj_list[graph.m_s]) {
            auto& edge{graph.m_edges[edge_index]};
            if(push(excess, edge, graph.m_edges[edge_index^1])) {
                if(edge.head != graph.m_t) {
                    highest = std::max(highest, labels[edge.head]);
                    active[labels[edge.head]].push_back(edge.head);
                }
            }
        }
        return highest;
    }

    /**
     * @brief Computes the maximum flow in a given flow network using 
     *        Goldberg's and Tarjan's push-relabel algorithm and the
     *        highest label selection rule.
     * 
     *
     *
     * @tparam flow_t Flow type.
     * @param graph The residual network.
     * @return The maximum flow.
     */
    template <typename flow_t>
    flow_t hi_push_relabel(data_structures::Graph<flow_t>& graph) {

        auto& adj_list{graph.m_adj_list};
        auto& edges{graph.m_edges};

        // labels. Initialized as shortest v-t distance for all vertices v
        //std::vector<int> labels(initialize_labels(graph));
        std::vector<int> labels(adj_list.size(), 0);
        labels[graph.m_s] = adj_list.size();

        // "current-arc" suggested by wikipedia.
        std::vector<int> current_edges(adj_list.size(), 0);

        // initialize excess
        std::vector<flow_t> excess(adj_list.size(), 0);
        excess[graph.m_s] = std::numeric_limits<flow_t>::max();

        // active nodes are now stored into buckets indexed by their labels
        // process active nodes from highest to lowest label
        std::vector<std::vector<int>> active(2*adj_list.size(), std::vector<int>{});

        // preflow + correct buckets of labels initialization
        int highest{initialize_buckets(graph, excess, active, labels)};
        // similar to the main loop of the generic push-relabel
        while(true) {
            // get the next active node with the highest label
            while(active[highest].empty()) {
                if(highest == 0) {
                    return excess[graph.m_t];
                }
                --highest;
            }
            int vertex{active[highest].back()};
            active[highest].pop_back();
            // usual discharge operation
            if(vertex == graph.m_s || vertex == graph.m_t) { continue; }
            while(excess[vertex] > 0) {
                if(current_edges[vertex] == adj_list[vertex].size()) {
                    current_edges[vertex] = relabel(graph, vertex, labels);
                    highest = labels[vertex];
                } else {
                    int edge_index{adj_list[vertex][current_edges[vertex]]};
                    auto& edge{edges[edge_index]};
                    if(edge.capacity > 0 && labels[vertex] == labels[edge.head]+1) {
                        if(push(excess, edge, edges[edge_index^1])) {
                            active[labels[edge.head]].push_back(edge.head);
                        }
                    } else {
                        ++current_edges[vertex];
                    }
                }
            }
        }
    }
}

#endif
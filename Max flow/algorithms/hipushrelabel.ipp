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
    void initialize_buckets(ds::Graph<flow_t>& graph, std::vector<flow_t>& excess, 
            std::vector<std::queue<int>>& active, const std::vector<int>& labels) {
        for(auto* edge : graph.m_adj_list[graph.m_s]) {
            if(push(excess, edge)) {
                if(edge->head != graph.m_t) {
                    active[labels[edge->head]].push(edge->head);
                }
            }
        }
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
    flow_t hi_push_relabel(ds::Graph<flow_t>& graph) {

        auto& adj_list{graph.m_adj_list};

        // labels. Initialized as shortest v-t distance for all vertices v
        std::vector<int> labels(graph.m_n, 0);
        labels[graph.m_s] = graph.m_n;

        // "current-arc" suggested by wikipedia.
        std::vector<int> current_edges(graph.m_n, 0);

        // initialize excess
        std::vector<flow_t> excess(graph.m_n, 0);
        excess[graph.m_s] = std::numeric_limits<flow_t>::max();

        // active nodes are now stored into buckets indexed by their labels
        // process active nodes from highest to lowest label
        std::vector<std::queue<int>> active(2*graph.m_n, std::queue<int>{});

        // preflow + correct buckets of labels initialization
        initialize_buckets(graph, excess, active, labels);
        int highest{0};
        
        // gap heuristic from wikipedia. gap[i] = number of vertices with label i
        std::vector<int> gap(2*graph.m_n, 0);
        gap[graph.m_s] = graph.m_n-1;

        // similar to the main loop of the generic push-relabel
        while(true) {
            // get the next active node with the highest label
            while(active[highest].empty()) {
                if(highest == 0) {
                    return excess[graph.m_t];
                }
                --highest;
            }
            int vertex{active[highest].front()};
            active[highest].pop();
            // usual discharge operation
            if(vertex == graph.m_s || vertex == graph.m_t) { continue; }
            while(excess[vertex] > 0) {
                if(current_edges[vertex] == adj_list[vertex].size()) {
                    current_edges[vertex] = relabel(graph, vertex, labels);
                    //update gap heuristic
                    --gap[highest];
                    ++gap[labels[vertex]];
                    // no more vertices with current highest (active) label
                    if(labels[vertex] < graph.m_n && gap[highest] == 0) {
                        for(int i{0}; i < graph.m_n; ++i) {
                            // vertices with highest < label < n can't be active, relabel them
                            if(highest < labels[i] && labels[i] < graph.m_n) {
                                --gap[labels[i]];
                                labels[i] = graph.m_n+1;
                            }
                        }
                    }
                    highest = labels[vertex];
                } else {
                    auto* edge{adj_list[vertex][current_edges[vertex]]};
                    if(edge->capacity > 0 && labels[vertex] == labels[edge->head]+1) {
                        if(push(excess, edge)) {
                            active[labels[edge->head]].push(edge->head);
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
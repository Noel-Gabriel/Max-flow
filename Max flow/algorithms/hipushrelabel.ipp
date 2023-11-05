#ifndef HI_PUSH_RELABEL_IPP
#define HI_PUSH_RELABEL_IPP

#include "../data structures/graph.h"
#include "pushrelabel.h"

#include <vector>
#include <queue>

namespace algorithms {

    /**
     * @brief Initializes the active buckets.
     *        See https://en.wikipedia.org/wiki/Push–relabel_maximum_flow_algorithm
     *        for the highest label selection rule.
     * 
     * @tparam T Flow type.
     * @param graph The residual network.
     * @param excess The excess at each vertex (inf for s, 0 every other vertex).
     * @param active The buckets.
     * @param labels The labels for each vertex.
     * @return int The highest label when initializing the buckets.
     */
    template <typename T>
    void initialize_buckets(ds::Graph<T>& graph, std::vector<T>& excess, 
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
     * @tparam T Flow type.
     * @param graph The residual network.
     * @return The value of a maximum flow.
     */
    template <typename T>
    T hi_push_relabel(ds::Graph<T>& graph) {
        // initialization
        auto& adj_list{graph.m_adj_list};

        // labels (or heights), all 0 except for the source at n (#vertices in the graph)
        std::vector<int> labels(graph.m_n, 0);
        labels[graph.m_s] = graph.m_n;

        // "current-arc" suggested by wikipedia.
        // https://en.wikipedia.org/wiki/Push–relabel_maximum_flow_algorithm
        std::vector<int> current_edges(graph.m_n, 0);

        // initialize excess
        std::vector<T> excess(graph.m_n, 0);
        excess[graph.m_s] = std::numeric_limits<T>::max();

        // active nodes are now stored into buckets indexed by their labels
        // process active nodes from highest to lowest label (all 0 at the start)
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
                    // excess at the sink at the end = value of a max flow
                    return excess[graph.m_t];
                }
                --highest;
            }
            int vertex{active[highest].front()};
            active[highest].pop();
            // usual discharge operation
            if(vertex == graph.m_s || vertex == graph.m_t) { continue; }
            while(excess[vertex] > 0) {
                // node still active, but no push operation possible -> relabel node, update gaps
                if(current_edges[vertex] == adj_list[vertex].size()) {
                    current_edges[vertex] = relabel(graph, vertex, labels);
                    //update gap heuristic
                    --gap[highest];
                    ++gap[labels[vertex]];
                    // no more vertices with current highest (active) label
                    if(labels[vertex] < graph.m_n && gap[highest] == 0) {
                        for(int i{0}; i < graph.m_n; ++i) {
                            // vertices with highest current label < label < n can't be active, relabel them to n+1
                            if(highest < labels[i] && labels[i] < graph.m_n) {
                                --gap[labels[i]];
                                labels[i] = graph.m_n+1;
                            }
                        }
                    }
                    // new highest label
                    highest = labels[vertex];
                } else {
                    auto* edge{adj_list[vertex][current_edges[vertex]]};
                    // push if edge not saturated and adjacent vertex at lower label (height)
                    if(edge->capacity > 0 && labels[vertex] == labels[edge->head]+1) {
                        // add adjacent vertex to active nodes if it was a first push to this vertex
                        if(push(excess, edge)) {
                            active[labels[edge->head]].push(edge->head);
                        }
                    } else {
                        // no push possible
                        ++current_edges[vertex];
                    }
                }
            }
        }
    }
}

#endif
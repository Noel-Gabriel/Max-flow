#ifndef EDMONDS_KARP_H
#define EDMONDS_KARP_H

#include "../data structures/graph.h"
#include "counter.h"


namespace algorithms {
    /**
     * @brief Computes the maximum flow of the given graph using 
     *        the ford-fulkerson method and a breath-first search 
     *        to find augmenting paths.
     * 
     * @tparam flow_t Flow type.
     * @param graph The flow network we want to compute the maximum flow of.
     * @return flow_t The maximum flow.
     */
    template <typename flow_t>
    flow_t edmonds_karp(data_structures::Graph<flow_t>& graph);
}

#include "edmondskarp.tpp"

#endif
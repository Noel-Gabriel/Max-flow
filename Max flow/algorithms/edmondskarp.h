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
     * @tparam T Flow type.
     * @param graph The residual network.
     * @return T The value of a maximum flow.
     */
    template <typename T>
    T edmonds_karp(ds::Graph<T>& graph);
}

#include "edmondskarp.ipp"

#endif

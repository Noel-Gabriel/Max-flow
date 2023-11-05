#ifndef DINIC_H
#define DINIC_H

#include "../data structures/graph.h"

namespace algorithms {

    /**
     * @brief Computes the maximum flow of the given graph using 
     *        Dinic's algorithm.
     * 
     * @tparam T Flow type.
     * @param graph The residual network.
     * @return T The value of a maximum flow.
     */
    template <typename T>
    T dinic(ds::Graph<T>& graph);
    
}

#include "dinic.ipp"

#endif

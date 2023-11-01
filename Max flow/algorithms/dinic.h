#ifndef DINIC_H
#define DINIC_H

#include "../data structures/graph.h"

namespace algorithms {

    /**
     * @brief Computes the maximum flow of the given graph using 
     *        Dinic's algorithm.
     * 
     * @tparam flow_t Flow type.
     * @param graph The flow network we want to compute the maximum flow of.
     * @return flow_t The maximum flow.
     */
    template <typename flow_t>
    flow_t dinic(ds::Graph<flow_t>& graph);
    
}

#include "dinic.ipp"

#endif

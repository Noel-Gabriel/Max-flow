#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include "../data structures/graph.h"

namespace algorithms {

    /**
     * @brief Computes the maximum flow of the given graph using 
     *        the ford-fulkerson method and a depth-first search 
     *        to find augmenting paths.
     * 
     * @tparam flow_t Flow type.
     * @param graph The flow network we want to compute the maximum flow of.
     * @return flow_t The maximum flow.
     */
    template <typename flow_t>
    flow_t ford_fulkerson(data_structures::Graph<flow_t>& graph);

}

#include "fordfulkerson.tpp"

#endif
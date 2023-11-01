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
     * @param graph The residual network.
     * @return flow_t The value of a maximum flow.
     */
    template <typename flow_t>
    flow_t ford_fulkerson(ds::Graph<flow_t>& graph);

}

#include "fordfulkerson.ipp"

#endif

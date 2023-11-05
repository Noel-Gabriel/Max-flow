#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include "../data structures/graph.h"

namespace algorithms {

    /**
     * @brief Computes the maximum flow of the given graph using 
     *        the ford-fulkerson method and a depth-first search 
     *        to find augmenting paths.
     * 
     * @tparam T Flow type.
     * @param graph The residual network.
     * @return T The value of a maximum flow.
     */
    template <typename T>
    T ford_fulkerson(ds::Graph<T>& graph);

}

#include "fordfulkerson.ipp"

#endif

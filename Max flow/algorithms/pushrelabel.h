#ifndef PUSH_RELABEL_H
#define PUSH_RELABEL_H

#include "../data structures/graph.h"

namespace algorithms {

    /**
     * @brief Computes the value of a maximum flow in the given graph using 
     *        Goldberg's and Tarjan's push-relabel algorithm.
     * 
     *
     * @tparam T Flow type.
     * @param graph The residual network.
     * @return The value of a maximum flow.
     */
    template <typename T>
    T push_relabel(ds::Graph<T>& graph);
        
}

#include "pushrelabel.ipp"

#endif

#ifndef PUSH_RELABEL_H
#define PUSH_RELABEL_H

#include "../data structures/graph.h"

namespace algorithms {

    /**
     * @brief Computes the value of a maximum flow in the given graph using 
     *        Goldberg's and Tarjan's push-relabel algorithm.
     * 
     *
     * @tparam flow_t Flow type.
     * @param graph The residual network.
     * @return The value of a maximum flow.
     */
    template <typename flow_t>
    flow_t push_relabel(ds::Graph<flow_t>& graph);
        
}

#include "pushrelabel.ipp"

#endif

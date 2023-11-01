#ifndef PUSH_RELABEL_H
#define PUSH_RELABEL_H

#include "../data structures/graph.h"

namespace algorithms {

    /**
     * @brief Computes the maximum flow in a given flow network using 
     *        Goldberg's and Tarjan's push-relabel algorithm.
     * 
     *
     * @tparam flow_t Flow type.
     * @param graph The residual network.
     * @return The maximum flow.
     */
    template <typename flow_t>
    flow_t push_relabel(ds::Graph<flow_t>& graph);
        
}

#include "pushrelabel.ipp"

#endif

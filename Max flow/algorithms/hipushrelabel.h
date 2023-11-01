#ifndef HI_PUSH_RELABEL_H
#define HI_PUSH_RELABEL_H

#include "../data structures/graph.h"

namespace algorithms {

    /**
     * @brief Computes the maximum flow in a given flow network using 
     *        Goldberg's and Tarjan's push-relabel algorithm and the
     *        highest label selection rule + gap relabel heuristic.
     * 
     *
     *
     * @tparam flow_t Flow type.
     * @param graph The residual network.
     * @return The value of a maximum flow.
     */
    template <typename flow_t>
    flow_t hi_push_relabel(ds::Graph<flow_t>& graph);
        
}

#include "hipushrelabel.ipp"

#endif
#ifndef GRAPH_READER_H
#define GRAPH_READER_H

#include "../data structures/graph.h"
#include "../PushRelabel.h"

#include <string_view>

struct PushRelabel;

namespace io {
    /**
     * @brief Reads a graph in dimacs format.
     * 
     * @param path path to dimacs file.
     * @return data_structures::Graph<int> The graph as a residual network.
     */
    ds::Graph<int> load_graph_from_file(std::string_view path);

    PushRelabel load_pr(std::string_view path);
    
}

#endif

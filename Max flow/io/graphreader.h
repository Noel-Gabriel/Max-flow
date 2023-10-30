#ifndef GRAPH_READER_H
#define GRAPH_READER_H

#include "../data structures/graph.h"
#include <string_view>

namespace io {

    /**
     * @brief Reads a graph in dimacs format.
     * 
     * @param path path to dimacs file.
     * @return data_structures::Graph<int> The graph as a residual network.
     */
    data_structures::Graph<int> load_graph_from_file(std::string_view path);
    
}

#endif
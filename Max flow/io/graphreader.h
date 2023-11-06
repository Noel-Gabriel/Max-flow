#ifndef GRAPH_READER_H
#define GRAPH_READER_H

#include "../data structures/graph.h"

#include <string_view>

namespace io {
    /**
     * @brief Reads a graph in dimacs format.
     * 
     * @param path path to the dimacs file.
     * @return ds::Graph<int> The graph as a residual network. (pynetgen generates only ints)
     */
    ds::Graph<int> load_graph_from_file(std::string_view path);

}

#endif

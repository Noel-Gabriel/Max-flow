#include "../data structures/graph.h"
#include "graphreader.h"

#include <string>
#include <string_view>
#include <fstream>
#include <sstream>

namespace io {

    /**
     * @brief Reads a graph in dimacs format. 
     * 
     * @param path path to dimacs file.
     * @return data_structures::Graph<int> The graph as a residual network.
     */
    data_structures::Graph<int> load_graph_from_file(std::string_view path) {
        std::ifstream file(path);
        std::string line{};
        if(!file.is_open()) {
            std::cout << "Error opening file.";
            std::exit(1);
        }
        // skip comments
        while(getline(file, line) && line[0] == 'c') {}
        // get number of vertices
        std::stringstream n_line(line);
        std::string n{};
        n_line >> n; // skip "p"
        n_line >> n; // skin problem definition "max" for maximum flow
        n_line >> n; // number of vertices
        data_structures::Graph<int> g{std::stoi(n)};
        // skip information about source and sink (always 0 and n-1)
        getline(file, line);
        getline(file, line);
        // read edges
        while(getline(file, line)) {
            std::stringstream edge_line(line);
            std::string in_v{};
            std::string out_v{};
            std::string cap{};
            edge_line >> in_v; // skip "a"
            edge_line >> in_v >> out_v >> cap; // read tail, head and capacity
            g.add_edge(std::stoi(in_v)-1, std::stoi(out_v)-1, std::stoi(cap));
        }
        return g;
    }
}
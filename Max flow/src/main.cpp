#include "../data structures/graph.h"

#include "../generators/ak/ak.h"
#include "../generators/genrmf/genrmf.h"

#include "../io/graphreader.h"
#include "../io/benchmark.h"

#include <iostream>
#include <chrono>
#include <filesystem>

int main() {

	// generate using genrmf and a = 10, b = 20, c1 = 1, c2 = 1000 and seed = 1
    generators::genrmf::generate(10, 20, 1, 1000, 1);
	// generate using ak and n = 2000
    generators::ak::generate(2000);

    std::vector<std::string> paths = {"test graphs/ak/",
                                       "test graphs/genrmf/"};

	// test each algorithm on the generated graphs
    for(auto& path : paths) {
		for(auto& file : std::filesystem::directory_iterator(path)) {
			ds::Graph<int> g{io::load_graph_from_file(file.path().string())};
			start<int>(g);
		}
	}

    return 0;
}

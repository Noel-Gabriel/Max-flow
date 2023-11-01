#include "data structures/graph.h"

#include "algorithms/fordfulkerson.h"
#include "algorithms/edmondskarp.h"
#include "algorithms/dinic.h"
#include "algorithms/pushrelabel.h"
#include "algorithms/hipushrelabel.h"
#include "algorithms/counter.h"

#include "io/graphreader.h"
#include "io/benchmark.h"

#include <iostream>
#include <chrono>
#include <map>
#include <cassert>


int main() {
    ds::Graph<int> g = io::load_graph_from_file("/Users/noel/Desktop/Max flow vscode/Max-flow/Max flow/test.dimacs");
    start<int>(g);
    return 0;
}

#include "data structures/graph.h"

#include "algorithms/fordfulkerson.h"
#include "algorithms/edmondskarp.h"
#include "algorithms/dinic.h"
#include "algorithms/pushrelabel.h"
#include "algorithms/hipushrelabel.h"
#include "algorithms/counter.h"

#include "io/ak.h"
#include "io/graphreader.h"
#include "io/benchmark.h"

#include <iostream>
#include <chrono>
#include <map>
#include <cassert>


int main() {
    generate_hard_problem("test graphs/aktest.dimacs", 1000);
    ds::Graph<int> g = io::load_graph_from_file("test graphs/aktest.dimacs");
    start<int>(g);
    return 0;
}

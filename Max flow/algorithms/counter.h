#ifndef COUNTER_H
#define COUNTER_H

/**
 * Not important. These are just counters that count the number of 
 * times ford-fulkerson, edmonds-karp and dinic's access an edge
 * during the computation of the bfs/dfs of each algorithm. 

 * Makes for a nice comparison and shows the improvement of dinic's over both
 * ford-fulkerson and edmonds-karp.
 */
namespace C {
    unsigned long long ff_edges_visited{0};
    unsigned long long ek_edges_visited{0};
    unsigned long long dinic_edges_visited{0};
}

#endif
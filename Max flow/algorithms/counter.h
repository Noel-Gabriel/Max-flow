#ifndef COUNTER_H
#define COUNTER_H

/**
 * Not important. These are just counters that count the number of 
 * times ford-fulkerson, edmonds-karp and dinic's access an edge
 * during the computation of the bfs/dfs of each algorithm. 

 * Makes for a nice comparison and shows the improvement of dinic's over both
 * ford-fulkerson and edmonds-karp.
 */
namespace counters {
    
    unsigned long long ff_edges_visited{0};
    unsigned long long ff_augmenting_paths{0};
    unsigned long long ek_edges_visited{0};
    unsigned long long ek_augmenting_paths{0};
    unsigned long long dinic_edges_visited{0};
    // considering the number of paths until a blocking flow is found
    unsigned long long dinic_augmenting_paths{0};
    unsigned long long hi_pr_pushes{0};
    unsigned long long hi_pr_relabels{0};
    unsigned long long pr_pushes{0};
    unsigned long long pr_relabels{0};
}

#endif
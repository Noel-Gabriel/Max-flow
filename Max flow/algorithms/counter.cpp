/**
 * Not important. These are just counters that count the number of 
 * times ford-fulkersn, edmonds-karp and dinic's access an edge
 * during the computation of the bfs/dfs of each algorithm. 

 * Makes for a nice comparison and shows the improvement of dinic's over both
 * ford-fulkerson and edmonds-karp (and edmonds-karp over ford-fulkerson).
 * 
 * Most of the time as expected
 * ff_edges_visited < ek_edges_visited < dinic_edges_visited
 */
namespace C {
    unsigned long long ff_edges_visited = 0;
    unsigned long long ek_edges_visited = 0;
    unsigned long long dinic_edges_visited = 0;
}
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

namespace ds {

    /**
     * @brief Class representing a residual network.
     * 
     * @tparam flow_t Flow type.
     */
    template <typename flow_t>
    class Graph {

        public:
            /**
            * @brief Represents an edge in the residual network.
            * 
            *        Stores the head and tail of the edge to facilitate the bfs and dfs.
            *        Stores the capacity and a pointer to the "reverse" edge in the residual network.
            */
            struct Edge {
                int tail{-1};
                int head{-1};
                flow_t capacity{-1};
                // reverse edge in the residual graph
                Edge* reverse{nullptr};
                // to restore the edge
                flow_t back_up_capacity{-1};

                // Edge constructor
                Edge(int t, int h, flow_t c);

                void restore() {capacity = back_up_capacity;}
            };

            /**
             * @brief The adjacency list.
             *        m_adj_list[v] = all outgoing edges from v
             */
            std::vector<std::vector<Edge*>> m_adj_list{};
            
            /**
             * @brief Number of vertices in the graph.
             */
            int m_n{};

            /**
             * @brief Source node. Initialized as 0
             */
            int m_s{};

            /**
             * @brief Sink node. Initialized as #vertices-1
             */
            int m_t{};

            /**
             * @brief Initializes the adjacency matrix to hold n vertices. Source 
             *        and sink are initialized as 0 and n-1 respectively, while the lists
             *        of edges for each vertex is empty.
             */
            Graph(int n);

            // destructor for edges
            ~Graph();

            /**
             * @brief Adds an edge to the current network. The reverse edge
             *        is added automatically.
             * 
             *
             * @param v_in An Integer, the tail of the edge. 
             * @param v_out An Integer, the head of the edge.
             * @param capacity Total capacity of the edge.
             */
            void add_edge(int v_in, int v_out, flow_t capacity);

            /**
             * @brief Restore each edge capacity.
             */
            void restore();

            // for debugging purposes
            void printGraph();
    };
}

#include "graph.ipp"

#endif

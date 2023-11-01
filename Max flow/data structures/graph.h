#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

namespace ds {

    /**
     * @brief Class representing a Residual network.
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
            *        Stores the capacity of the edge.
            */
            struct Edge {
                int tail{-1};
                int head{-1};
                flow_t capacity{-1};
                // reverse edge in the residual graph
                Edge* reverse{nullptr};
                // to restore the edge
                flow_t back_up_capacity{-1};

                Edge(int t, int h, flow_t c);

                void restore() {capacity = back_up_capacity;}
            };

            /**
             * @brief Initializes the adjacency matrix to hold n vertices. Source 
             *        and sink are initialized as 0 and n-1, while the adjacency list and
             *        edge list are empty.
             */
            Graph(int n);

            ~Graph();

            /**
             * @brief Adds an edge to the current network. The reverse edge
             *        is added automatically.
             * 
             *
             * @param vertex_in An Integer, the tail of the edge. 
             * @param vertex_out An Integer, the head of the edge.
             * @param capacity Total capacity of the edge.
             */
            void add_edge(int vertex_in, int vertex_out, flow_t capacity);

            /**
             * @brief Restores the last saved graph.
             */
            void restore();

            /**
             * @brief The adjacency list.
             *        m_adj_list[v] are indices for all the edges in m_edges that
             *        have vertex v as their tail.
             */
            std::vector<std::vector<Edge*>> m_adj_list{};


            // for debugging purposes
            void printGraph();
            
            /**
             * @brief Number of vertices in the graph.
             */
            int m_n{};

            /**
             * @brief Source node.
             */
            int m_s{};

            /**
             * @brief Sink node.
             */
            int m_t{};
    };

}

#include "graph.ipp"

#endif

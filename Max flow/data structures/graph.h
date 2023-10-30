#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

namespace data_structures {

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

                Edge(int h, int t, flow_t c);
            };

            /**
             * @brief Initializes the adjacency matrix to hold n vertices. Source 
             *        and sink are initialized as 0 and n-1, while the adjacency list and
             *        edge list are empty.
             */
            Graph(int n);

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
             * @brief Duplicates the current graph.
             */
            void save();

            /**
             * @brief Restores the last saved graph.
             */
            void restore();

            /**
             * @brief The adjacency list.
             *        m_adj_list[v] are indices for all the edges in m_edges that
             *        have vertex v as their tail.
             */
            std::vector<std::vector<int>> m_adj_list{};

            /**
             * @brief Vector containg all the edges in the flow network.
             *        Every edge in the graph is on an even index and the
             *        reverse edge in the residual graph is stored right after.
             * 
             *        I.e: reverse edge for m_edges[2] is m_edges[3]
             */
            std::vector<Edge> m_edges{};

            // for debugging purposes
            void printGraph() const;

            /**
             * @brief Source node.
             */
            int m_s{};

            /**
             * @brief Sink node.
             */
            int m_t{};
        
        private:
            // enumerates new edges added to the network.
            int m_edges_index{0};

            // saves the current graph. All algorithms act on the capacity of and edge
            // and we need to be able to restore the graph to try
            // different algorithms on the same graph.
            std::vector<std::vector<int>> m_adj_list_backup{};
            std::vector<Edge> m_edges_backup{};
    };

}

#include "graph.tpp"

#endif
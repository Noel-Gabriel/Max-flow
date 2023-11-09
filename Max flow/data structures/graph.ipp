#ifndef GRAPH_IPP
#define GRAPH_IPP

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cassert>
#include <random>
#include <algorithm>

namespace ds {

    // Edge constructor
    template <typename T>
    Graph<T>::Edge::Edge(int t, int h, T c)
        : tail{t}
        , head{h}
        , capacity{c} 
        , reverse{nullptr}
        , back_up_capacity{c} {}

    /**
     * @brief Initializes the adjacency matrix to hold n vertices. Source 
     *        and sink are initialized as 0 and n-1 respectively, while the lists
     *        of edges for each vertex is empty.
     */
    template <typename T>
    Graph<T>::Graph(int n) 
        : m_adj_list(n)
        , m_n{n}
        , m_s{0}
        , m_t{n-1} {}

    // Destructor for edges
    template <typename T>
    Graph<T>::~Graph() {
        for(int i{0}; i < m_adj_list.size(); ++i) {
            for(int j{0}; j < m_adj_list[i].size(); ++j) {
                delete m_adj_list[i][j];
            }
        }
    }

    /**
     * @brief Adds an edge to the current network. The reverse edge
     *        is added automatically.
     * 
     *
     * @param v_in An Integer, the tail of the edge. 
     * @param v_out An Integer, the head of the edge.
     * @param capacity Total capacity of the edge.
     */
    template <typename T>
    void Graph<T>::add_edge(int v_in, int v_out, T capacity) {
        // no self loops
        if(v_in == v_out) { return; }

        Edge* edge = new Edge{v_in, v_out, capacity};
        Edge* reverse = new Edge{v_out, v_in, 0};

        edge->reverse = reverse;
        reverse->reverse = edge;

        // add edge + reverse edge
        m_adj_list[v_in].push_back(edge);
        m_adj_list[v_out].push_back(reverse);
    }

    /**
     * @brief Shuffles the adjacency list.
     */
    template <typename T>
    void Graph<T>::shuffle_edges() {
        for(int i{0}; i < m_n; ++i) {
            auto rd{std::random_device{}};
            auto rng{std::default_random_engine{rd()}};
            std::shuffle(m_adj_list[i].begin(), m_adj_list[i].end(), rng);
        }
    }

    /**
     * @brief Restore each edge capacity.
     */
    template <typename T>
    void Graph<T>::restore() {
        for(int i{0}; i < m_adj_list.size(); ++i) {
            for(int j{0}; j < m_adj_list[i].size(); ++j) {
                m_adj_list[i][j]->restore();
            }
        }
    }

    // for debugging purposes
    template <typename T>
    void Graph<T>::print_graph() {
        std::cout << "Source: " << m_s << "\n";
        std::cout << "Sink: " << m_t << "\n";
        std::cout << "Edges: \n";
        for(int i{0}; i < m_adj_list.size(); ++i) {
            for(int j{0}; j < m_adj_list[i].size(); ++j) {
                Edge* edge = m_adj_list[i][j];
                std::cout << edge->tail+1 << " -" << edge->capacity << "-> " << edge->head+1 << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

#endif
#ifndef GRAPH_IPP
#define GRAPH_IPP

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cassert>

namespace ds {

    template <typename flow_t>
    Graph<flow_t>::Edge::Edge(int t, int h, flow_t c)
        : tail{t}
        , head{h}
        , capacity{c} 
        , reverse{nullptr}
        , back_up_capacity{c} {}

    template <typename flow_t>
    Graph<flow_t>::Graph(int n) 
        : m_adj_list(n)
        , m_n{n}
        , m_s{0}
        , m_t{n-1} {}

    template <typename flow_t>
    Graph<flow_t>::~Graph() {
        for(int i{0}; i < m_adj_list.size(); ++i) {
            for(int j{0}; j < m_adj_list[i].size(); ++j) {
                delete m_adj_list[i][j];
            }
        }
    }

    template <typename flow_t>
    void Graph<flow_t>::add_edge(int v_in, int v_out, flow_t capacity) {
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

    template <typename flow_t>
    void Graph<flow_t>::restore() {
        for(int i{0}; i < m_adj_list.size(); ++i) {
            for(int j{0}; j < m_adj_list[i].size(); ++j) {
                m_adj_list[i][j]->restore();
            }
        }
    }

    // for debugging purposes
    template <typename flow_t>
    void Graph<flow_t>::printGraph() {
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
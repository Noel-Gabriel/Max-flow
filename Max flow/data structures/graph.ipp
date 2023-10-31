#ifndef GRAPH_IPP
#define GRAPH_IPP

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

namespace data_structures {

    template <typename flow_t>
    Graph<flow_t>::Edge::Edge(int t, int h, flow_t c)
        : tail{t}
        , head{h}
        , capacity{c} {}

    template <typename flow_t>
    Graph<flow_t>::Graph(int n) 
        : m_adj_list(n)
        , m_s{0}
        , m_t{n-1} {}

    template <typename flow_t>
    void Graph<flow_t>::add_edge(int vertex_in, int vertex_out, flow_t capacity) {
        // no self loops
        if(vertex_in == vertex_out) { return; }
        // add the edge
        m_edges.emplace_back(vertex_in, vertex_out, capacity);
        // the reverse edge in the residual network, capacity = 0 since now flow has been pushed yet.
        m_edges.emplace_back(vertex_out, vertex_in, 0);
        // add edges in order
        m_adj_list[vertex_in].push_back(m_edges_index++);
        m_adj_list[vertex_out].push_back(m_edges_index++);
    }

    template <typename flow_t>
    void Graph<flow_t>::save() {
        if(m_adj_list_backup.empty()) {
            m_adj_list_backup = m_adj_list;
            m_edges_backup = m_edges;
        }
    }

    template <typename flow_t>
    void Graph<flow_t>::restore() {
        m_adj_list = m_adj_list_backup;
        m_edges = m_edges_backup;
    }

    // for debugging purposes
    template <typename flow_t>
    void Graph<flow_t>::printGraph() const {
        std::cout << "Source: " << m_s << "\n";
        std::cout << "Sink: " << m_t << "\n";
        std::cout << "Edges: \n";
        for(int i{0}; i < m_adj_list.size(); ++i) {
            for(int j{0}; j < m_adj_list[i].size(); ++j) {
                Edge edge = m_edges[m_adj_list[i][j]];
                std::cout << i << " -" << edge.capacity << "-> " << edge.head << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

}

#endif
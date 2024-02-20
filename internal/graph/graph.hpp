#ifndef Graph_H
#define Graph_H

#include "edge.hpp"
#include <vector>
#include <set>
#include <map>

template <typename T>
using Adj_matrix_T = std::vector<std::vector<T>>; //now MyFilter is a typedef for  Filt 


template <typename T> class Graph_T {
    protected:
        size_t n;       // number of nodes
        size_t m;       // number of edges
        T null_value;
        Adj_matrix_T<T> adj_matrix; // graph where the edge (u,v) is stored as adj[u][v]
        std::vector<Edge_T<T>> edges_list;

    public:
        Graph_T(int n, T zero_value);
        Graph_T(int n, std::vector<Edge_T<T>> edges, T zero_value);

        int getVertexesSize();
        std::vector<int> getVertices();

        int getEdgesSize();
        std::vector<Edge_T<T>> getEdges();
        T getEdge(int u, int v);

        T getLambda(int u);
        T getNull();
        void addEdge(int u, int v, T a);
        void printGraph();
        void printGraphHashed();
        void storeGraphFile(std::string name, std::string filename);
};

#include "graph.cpp"

#endif
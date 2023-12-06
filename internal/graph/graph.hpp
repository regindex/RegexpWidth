#ifndef Graph_H
#define Graph_H

#include "edge.hpp"
#include <vector>
#include <set>
#include <map>

typedef std::vector<char> vc;
typedef std::vector<vc> vcc;

// TODO
// check for the ordering of the nodes
bool lex_compare(const char &a, const char &b);

class Graph_h {
    protected:
        size_t n;       // number of nodes
        size_t m;       // number of edges
        vcc adj_matrix; // graph where the edge (u,v) is stored as adj[u][v]

    public:
        Graph_h(int n);

        int getVertexesSize();
        std::vector<int> getVertices();

        int getEdgesSize();
        std::vector<Edge_h> getEdges();
        char getEdge(int u, int v);

        char &at(size_t row, size_t col);

        std::set<char, decltype(&lex_compare)> getLambda(int u);
        char getMaxLambda(int u);
        char getMinLambda(int u);
        std::pair<char, char> getMinMaxLambda(int u);

        void addEdge(int u, int v, char a);

        void printGraph();
        void storeGraphFile(std::string name, std::string filename);
};

#endif
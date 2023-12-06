#include "graph.hpp"
#include <iostream>
#include <fstream>
#include <numeric>

//TODO
//check for the ordering of the nodes
bool lex_compare(const char& a, const char& b) {
    if (a == '#')
        return true;
    if (a <= b)
        return true;
    else 
        return false;
}

Graph_h::Graph_h(int n) {
    this->n = n;
    this->m = m;
    this->adj_matrix.resize(n, vc(n, ' '));
}

char& Graph_h::at(size_t row, size_t col) {
    return this->adj_matrix.at(row).at(col);
}

//Return the number of vertices
int Graph_h::getVertexesSize() {
    return this->n;
}

//generate and return an array with the vertexes indexes
std::vector<int> Graph_h::getVertices() {
    std::vector<int> vert(n);
    std::iota(vert.begin(), vert.end(), 0);
    return vert;   
}

//Return the number of vertices
int Graph_h::getEdgesSize() {
    int count = 0;
    for(int i = 0; i < this->n; ++i) {
        for(int j = 0; j < this->n; ++j) {
            if(this->adj_matrix.at(i).at(j) != ' ') ++count;
        }    
    }
 
    return count;
}

//create and return the edge list of the graph
std::vector<Edge_h> Graph_h::getEdges() {
     std::vector<Edge_h> edges;
    for (size_t i = 0; i < this->n; i++) {
        for(int j = 0; j < n; j++) {
            if(adj_matrix.at(i).at(j) != ' ') {
                edges.push_back(Edge_h(i, j, adj_matrix.at(i).at(j)));
            }
        }
    }
    return edges;
}

//return the label of the edge (u,v)
char Graph_h::getEdge(int u, int v) {
    return this->adj_matrix.at(u).at(v);
}

//return the ordered set of the label entering in node u
std::set<char,decltype(&lex_compare)> Graph_h::getLambda(int u) {
    std::set<char, decltype(&lex_compare)> lambda(&lex_compare);
    for (size_t i = 0; i < this->n; i++) {
        if(adj_matrix.at(i).at(u) != ' ') {
            lambda.insert(adj_matrix.at(i).at(u));
        }
    }
    return lambda;
}

//return the max label entering in node u
char Graph_h::getMaxLambda(int u) {
    auto lambda = getLambda(u);
     if(lambda.size() == 0)
        return '#';
    else
        return *lambda.begin();
}

//return the min label entering in node u
char Graph_h::getMinLambda(int u) {
    auto lambda = this->getLambda(u);
    if(lambda.size() == 0)
        return '#';
    else
        return *lambda.rbegin();
}

//return a pair with the min and max labels entering in node u
std::pair<char,char> Graph_h::getMinMaxLambda(int u) {
    auto lambda = this->getLambda(u);
    if(lambda.size() == 0)
        return std::make_pair('#','#');
    else
       return std::make_pair(*lambda.begin(),*lambda.rbegin());
}

//add edge (u,v,a) to the graph
void Graph_h::addEdge(int u, int v, char a) {
    this->adj_matrix.at(u).at(v) = a;
}

//print the graph adj matrix
void Graph_h::printGraph() {
    std::cout << "  ";
    for (size_t i = 0; i < this->n; i++)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    for (size_t i = 0; i < this->n; ++i) {
        std::cout << i << " ";
        for (size_t j = 0; j < this->n; j++) {
            std::cout << this->adj_matrix.at(i).at(j) << ' ';
        }
        std::cout << std::endl;    
    }
}

//print the graph in the dot format into the file passed as argument
void Graph_h::storeGraphFile(std::string name, std::string filename) {
    std::ofstream output_file;
    output_file.open(filename);
    output_file << "digraph " << name << "{" << std::endl;
    auto edges = this->getEdges();

    for(auto el : edges) {
        output_file << el.getV1() << " -> "<< el.getV2() << " [ label = \" " << el.getLabel() << " \" ];" << std::endl;
    }
    output_file << "}" << std::endl;
    
    output_file.close();
}


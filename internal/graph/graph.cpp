#include "graph.hpp"
#include "edge.hpp"
#include <iostream>
#include <fstream>
#include <numeric>

template <typename T> 
bool compare(const T& a, const T& b) {
    std::cout << "The used type is not already implemented." << std::endl;
    exit(0);
}

template <> 
bool compare<char>(const char& a, const char& b) {
    if (a == ' ')
        return true;
    if (a <= b)
        return true;
    else 
        return false;
}

template <> 
bool compare<std::string>(const std::string& a, const std::string& b) {
    if(a==b)
        return true;
    if(a == "")
        return true;
    if(b == "")
        return false;
    
    std::size_t a_hash = std::hash<std::string>{}(a), b_hash = std::hash<std::string>{}(b);
    if (a_hash <= b_hash)
        return true;
    else 
        return false;
}

template <typename T> 
bool compare_not_eq(const T& a, const T& b) {
    std::cout << "The used type is not already implemented." << std::endl;
    exit(0);
}

template <> 
bool compare_not_eq<char>(const char& a, const char& b) {
    if (a == ' ')
        return true;
    if (b == ' ')
        return false;
    if (a < b)
        return true;
    else 
        return false;
}

template <> 
bool compare_not_eq<std::string>(const std::string& a, const std::string& b) {
    if(a == "")
        return true;
    if( b== "")
        return false;
    std::size_t a_hash = std::hash<std::string>{}(a), b_hash = std::hash<std::string>{}(b);
    if (a_hash < b_hash)
        return true;
    else 
        return false;
}

 
template <typename T> 
Graph_T<T>::Graph_T(int n, T null_value) {
    this->n = n;
    this->m = 0;
    this->null_value = null_value;
    this->adj_matrix.resize(n, std::vector<T>(n, null_value));
}

template <typename T> 
Graph_T<T>::Graph_T(int n, std::vector<Edge_T<T>> edges, T null_value) {
    this->n = n;
    this->m = 0;
    this->null_value = null_value;
    this->adj_matrix.resize(n, std::vector<T>(n, null_value));
    for (Edge_T<T> e : edges) {
        this->adj_matrix.at(e.getV1()).at(e.getV2()) = e.getLabel();
        ++m;
    }
    this->edges_list = edges;
}


//Return the number of vertices 
template <typename T> 
int Graph_T<T>::getVertexesSize() {
    return this->n;
}

//generate and return an array with the vertexes indexes
template <typename T> 
std::vector<int> Graph_T<T>::getVertices() {
    std::vector<int> vert(n);
    std::iota(vert.begin(), vert.end(), 0);
    return vert;   
}

//Return the number of vertices
template <typename T>
int Graph_T<T>::getEdgesSize() {
    return m;
}

//create and return the edge list of the Graph_T
template <typename T>
std::vector<Edge_T<T>> Graph_T<T>::getEdges() {
    return this->edges_list;
}

//return the label of the edge (u,v)
template <typename T>
T Graph_T<T>::getEdge(int u, int v) {
    return this->adj_matrix.at(u).at(v);
}


//add edge (u,v,a) to the Graph_T
template <typename T>
void Graph_T<T>::addEdge(int u, int v, T a) {
    this->m += 1;
    this->adj_matrix.at(u).at(v) = a;
    this->edges_list.push_back(Edge_T<T>(u,v,a));
}

template <typename T>
T Graph_T<T>::getLambda(int u) {
    T lambda = this->null_value;
    for(int i = 0; i < n; ++i) {
        if(this->adj_matrix.at(i).at(u) != this->null_value) {
            lambda = this->adj_matrix.at(i).at(u);
            break;
        }
    }
    return lambda;
}


template <typename T>
T Graph_T<T>::getNull() {
    return this->null_value;
}


//print the Graph_T adj matrix
template <typename T>
void Graph_T<T>::printGraph() {
    for(auto e : this->edges_list) {
        std::cout << e.getV1() << " " << e.getV2() << " " << e.getLabel() << std::endl;
    }
}

template <typename T>
void Graph_T<T>::printGraphHashed() {
    for(auto e : this->edges_list) {
        std::size_t e_hash = std::hash<std::string>{}(e.getLabel());
        std::cout << e.getV1() << " " << e.getV2() << " " << e_hash << std::endl;
    }
}



//print the Graph_T in the dot format into the file passed as argument
template <typename T>
void Graph_T<T>::storeGraphFile(std::string name, std::string filename) {
    std::ofstream output_file;
    output_file.open(filename);
    output_file << "diGraph_T " << name << "{" << std::endl;
    auto edges = this->getEdges();

    for(auto el : edges) {
        output_file << el.getV1() << " -> "<< el.getV2() << " [ label = \" " << el.getLabel() << " \" ];" << std::endl;
    }
    output_file << "}" << std::endl;
    
    output_file.close();
}


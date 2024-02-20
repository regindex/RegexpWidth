#ifndef PartialOrder_H
#define PartialOrder_H

#include "graph/graph.hpp"
#include <string>

typedef std::vector<std::vector<bool>> Vbb;

class Order {
    private:
        size_t n;
        Vbb incidenceMatrix;
    public:
        template <typename T>
        Order(Graph_T<T>& G);
        //int computeWidth();
        void printIncidenceMatrix();
        Vbb getIncidenceMatrix();
        void printOrder(std::string output_file_name);
        void printTransitiveReduction(std::string output_file_name);
        Vbb getTransitiveReduction();
        void setTransitiveReduction();
};

#include "partialOrder.cpp"

#endif
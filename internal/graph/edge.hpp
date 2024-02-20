#ifndef Edge_H
#define Edge_H

#include <cstddef>


template <typename T> class Edge_T {
    protected:
        size_t v1;
        size_t v2;
        T label;
    public:
        Edge_T(int v1, int v2, T label);
        size_t getV1();
        size_t getV2();
        T getLabel();
};

#include "edge.cpp"

#endif
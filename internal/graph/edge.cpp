#include "edge.hpp"


template <typename T> Edge_T<T>::Edge_T(int v1, int v2, T label) { 
    this->v1 = v1; 
    this->v2 = v2; 
    this->label = label;
}

template <typename T> size_t Edge_T<T>::getV1(){
    return this->v1;
}

template <typename T> size_t Edge_T<T>::getV2(){
    return this->v2;
}

template <typename T> T Edge_T<T>::getLabel(){
    return this->label;
}
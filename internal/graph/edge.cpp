#include "edge.hpp"


Edge_h::Edge_h(int v1, int v2,char label) { 
    this->v1 = v1; 
    this->v2 = v2; 
    this->label = label;
}

int Edge_h::getV1(){
    return this->v1;
}

int Edge_h::getV2(){
    return this->v2;
}

char Edge_h::getLabel(){
    return this->label;
}
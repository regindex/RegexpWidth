#ifndef Edge_H
#define Edge_H

class Edge_h {
    protected:
        int v1;
        int v2;
        char label;
    public:
        Edge_h(int v1, int v2,char label);
        int getV1();
        int getV2();
        char getLabel();
};

#endif
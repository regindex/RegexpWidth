#include "partialOrder.hpp"
#include<iostream>
#include<queue>
#include <fstream>


template <typename T>
Order::Order(Graph_T<T>& G) {

    this->n = G.getVertexesSize();

    /*create the edge
        u1 -> u2
        v1 -> v2

        (u1,v1) -> (u2,v2)
    */
    std::vector<T> lambdas;
    for(size_t i = 0; i < n; ++i) {
        lambdas.push_back(G.getLambda(i));
    }
     
    this->incidenceMatrix.resize(n, std::vector<bool>(n,1));
    //we need to have 1 at [u][v] when u <= v
    //we set the wrong pairs to false and we propagate forward
    std::queue<std::pair<int,int>> visit_q; 

    for (size_t u = 0; u < n; ++u) {
        for (size_t v = 0; v < n; ++v) {
            //max_lambda(u) > min_lambda(v)
            //set to false because u !< v
            //reflexive due to total order of the alphabet
            //if the pair is marked we skip it 
            if(incidenceMatrix.at(u).at(v) == 1) {
                if( !compare(lambdas.at(u), lambdas.at(v) )) {
                    incidenceMatrix.at(u).at(v) = 0;

                    //propagate
                    visit_q.push(std::make_pair(u,v));
                    //BFS visit
                    while(visit_q.size() != 0) {
                        //extract the pair
                        std::pair<int,int> current_node = visit_q.front(); visit_q.pop();
                        int u1 = current_node.first, v1 = current_node.second;

                        //put all pair of nodes reached by (u,v) into the queue 
                        for (size_t u2 = 0; u2 < this->n; ++u2) {
                            for (size_t v2 = 0; v2 < this->n; ++v2) {
                                //if the pair u2 v2 can be reached from the same 
                                if( G.getEdge(u1,u2) != G.getNull() && G.getEdge(u1,u2) == G.getEdge(v1,v2) && incidenceMatrix.at(u2).at(v2) == 1) {
                                    /* std::cout << "marked pairs" << std::endl;
                                    std::cout << u1 << " " << u2 << std::endl;
                                    std::cout << v1 << " " << v2 << std::endl; */
                                    incidenceMatrix.at(u2).at(v2) = 0;
                                    visit_q.push(std::make_pair(u2,v2));
                                }
                            }
                        }
                    }
                    /* std::cout<< "--------------------------------" << std::endl;
                    printIncidenceMatrix();
                    std::cout<< "--------------------------------" << std::endl; */
                }
            }
        }
    }
    for (size_t i = 0; i < this->n; i++) {
        incidenceMatrix.at(i).at(i) = 1;
    }
    
}

void Order::printIncidenceMatrix() {
    std::cout << "  ";
    for (size_t i = 0; i < this->n; i++)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    for (size_t i = 0; i < this->n; ++i) {
        std::cout << i << " ";
        for (size_t j = 0; j < this->n; j++) {
            std::cout << this->incidenceMatrix.at(i).at(j) << ' ';
        }
        std::cout << std::endl;    
    }}

Vbb Order::getIncidenceMatrix() {
    return this->incidenceMatrix;
}

void Order::printOrder(std::string output_file_name) {
    size_t m = 0;
    //iterate through the matrix
    for (size_t i = 0; i < this->n; ++i) {
        for (size_t j = 0; j < this->n; ++j) {
            if(this->incidenceMatrix.at(i).at(j) == 1) {
                ++m;
            }
        }
    }
    std::ofstream output_file;
    output_file.open(output_file_name);
    output_file << this->n << " " << m << std::endl;

    //iterate through the matrix
    for (size_t i = 0; i < this->n; ++i) {
        for (size_t j = 0; j < this->n; ++j) {
            if(this->incidenceMatrix.at(i).at(j) == 1) {
                output_file << i+1 << " " << j+1 << std::endl;
            }
        }
    }
    output_file.close();
}


Vbb Order::getTransitiveReduction() {
    Vbb trans(this->incidenceMatrix);

    for(int k = 0; k<this->n; ++k)
        for(int i = 0; i<this->n; ++i)
            for(int j = 0; j<this->n; ++j)
                if( trans.at(k).at(i) && trans.at(i).at(j) && i != k && i != j) trans.at(k).at(j) = 0;
    return trans;
}

void Order::setTransitiveReduction() {
    Vbb trans(this->incidenceMatrix);

    for(int k = 0; k<this->n; ++k)
        for(int i = 0; i<this->n; ++i)
            for(int j = 0; j<this->n; ++j)
                if( trans.at(k).at(i) && trans.at(i).at(j) && i != k && i != j) trans.at(k).at(j) = 0;
    this->incidenceMatrix = trans;
}

void Order::printTransitiveReduction(std::string output_file_name) {
    //transitive reduction of incidence matrix
    Vbb trans(getTransitiveReduction());
    
    //print to file output
    std::ofstream output_file;
    output_file.open(output_file_name);
    size_t m = 0;
    for (size_t i = 0; i < this->n; ++i) {
        for (size_t j = 0; j < this->n; ++j) {
            if(trans.at(i).at(j) == true) {
                ++m;
            }
        }
    }

    output_file << this->n << " " <<    m << std::endl;
    for (size_t i = 0; i < this->n; ++i) {
        for (size_t j = 0; j < this->n; ++j) {
            if(trans.at(i).at(j) == true && i != j) {
                output_file << i+1 << " " << j+1 << std::endl;
            }
        }
    }
    output_file.close();
}

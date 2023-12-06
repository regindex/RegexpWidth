#ifndef VERIFICATOR_HPP
#define VERIFICATOR_HPP

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

#include "graph/graph.hpp"
#include "partialOrder.hpp"

typedef std::vector<std::vector<bool> > Vbb;

//check if the order over the quotient graph is a co-lex partial order
std::pair<bool,bool> _verificator(Graph_h &quotient, Vbb &order) {
    size_t n = quotient.getVertexesSize();


    bool co_lex = true;
    std::vector<std::pair<char,char>> lambdas;
    for(size_t i = 0; i < n; ++i) {
        lambdas.push_back(quotient.getMinMaxLambda(i));
    }
     

    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < n; ++j) {
            //max < min
            if( lambdas.at(i).second == '#' || lambdas.at(i).second < lambdas.at(j).first) {
                if(order.at(i).at(j) == false)
                    co_lex = false;
            }
        }        
    }

    for(size_t u = 0; u < n; ++u) {
        for(size_t v = 0; v < n; ++v) {
            for(size_t u1 = 0; u1 < n; ++u1) {
                for(size_t v1 = 0; v1 < n; ++v1) {
                    //(u1,u),(v1,v) in E
                    if(quotient.getEdge(u1,u) != ' ' && quotient.getEdge(v1, v) != ' ') {
                        //same label and u < v
                        if(lambdas.at(u) == lambdas.at(v) && order.at(u).at(v) && u != v) {
                            //u1 < v1 ?
                            if(order.at(u1).at(v1) == false) {
                                co_lex = false;
                            }
                        }
                    }
                }
            }
        }
    }
    
    bool partial = true;
    
    for (size_t a = 0; a < order.size(); ++a) {
        for (size_t b = 0; b < order.size(); ++b) {
            for (size_t c = 0; c < order.size(); ++c) {
                if(order.at(a).at(b) && order.at(b).at(c)) {
                    if(!order.at(a).at(c))
                        partial = false;
                }
        
            }   
        }    
    }
    
    for (size_t a = 0; a < order.size(); ++a) {
        for (size_t b = 0; b < order.size(); ++b) {
            if(a == b) {
                if(order[a][b] != 1)
                    partial = false ;
            } else {
                if(order[a][b]) {
                    if(order[b][a])
                        partial = false;
                }
            }
        }
    }
    
    return std::make_pair(co_lex, partial);
}


//compute the quotient graph and the order from the preorder
std::pair<Graph_h, Vbb> compute_quotient(Graph_h& graph, PartialOrder pre) {
    std::unordered_map<int, std::unordered_set<int>> convex_sets;
    Vbb preorder = pre.getIncidenceMatrix();

    std::unordered_set<int> v_set;
    for (size_t i = 0; i < graph.getVertexesSize(); i++) {
        v_set.insert(i);
    }
    
    int count = 0;
    for (size_t i = 0; i < graph.getVertexesSize(); ++i) {
        if(v_set.count(i) > 0) {
            std::unordered_set<int> my_set;
            for (size_t j = 0; j < graph.getVertexesSize(); ++j) {    
                if(preorder[i][j] == 1 && preorder[j][i] == 1) {
                    my_set.insert(i);
                    my_set.insert(j);
                    v_set.erase(i);
                    v_set.erase(j);
                }
            }
            convex_sets.insert(std::make_pair(count, my_set));
            ++count;
        }
    }
    
    Graph_h quotient(convex_sets.size());
    Vbb new_order(convex_sets.size(), std::vector<bool>(convex_sets.size(),0));

    for (auto p1 : convex_sets) {

        size_t new_node1 = p1.first;
        auto   node_set1 = p1.second;
    
        for (auto p2 : convex_sets) {

            size_t new_node2 = p2.first;
            auto   node_set2 = p2.second;

            for(auto old_node1 : node_set1) {
                for(auto old_node2 : node_set2) {
                    auto e = graph.getEdge(old_node1, old_node2);
                    if(e != ' ') {
                        quotient.addEdge(new_node1, new_node2, e);
                    }
                    if(preorder[old_node1][old_node2]) {
                        new_order[new_node1][new_node2] = 1;
                    }
                }
            }
            
        }
    }

    for (size_t i = 0; i < quotient.getVertexesSize(); i++) {
        for (size_t j = 0; j < quotient.getVertexesSize(); j++) {
            if(new_order[i][j]) {
                new_order.at(i).at(j) = 1;
            }
        }
    }




    return std::make_pair(quotient, new_order);
}

/* Collapse the original graph to the quotient graph 
 * and compute the partial order from the preorder
 * 
 *  After that it check if the order of the quotient graph
 *  is a co-lex partial order
 */
std::pair<bool,bool> check_orders(Graph_h& graph, PartialOrder& pre) {
    auto objects = compute_quotient(graph, pre);
    auto results = _verificator(objects.first, objects.second);

    return results;
}


#endif
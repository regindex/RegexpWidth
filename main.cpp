#include "internal/graph/graph.hpp"
#include "internal/partialOrder.hpp"
#include "internal/mpc.hpp"
#include "internal/conversion/nfa.hpp"
#include "internal/conversion/glushkov-automaton.hpp"
#include "internal/verificator.hpp"

#include <vector>
#include <iostream>

#include <string>

#define CHAIN 0
#define PARTIAL 1
#define GL 2
#define QUOTIENT 3
#define VERIFICATOR 4

#define SUM 0
#define QUESTION 1
#define BAR 2
#define STAR 3


void parse_flags(int arg, char** argv, std::vector<std::string> &files, std::vector<bool> &flags) {

    std::string str = "";
    for (size_t i = 1; i < arg; ++i) {
        str.append(argv[i]);
        str.append(" ");
        if(strcmp(argv[i],"-chain") == 0) {
            flags.at(CHAIN) = true;
            ++i;
            files.at(CHAIN) = argv[i];
        }
        if(strcmp(argv[i],"-partial") == 0) {
            flags.at(PARTIAL) = true;
            ++i;
            files.at(PARTIAL) = argv[i];
        }
        if(strcmp(argv[i],"-gl") == 0) {
            flags.at(GL) = true;
            ++i;
            files.at(GL) = argv[i];
        }
        if(strcmp(argv[i],"-quotient") == 0) {
            flags.at(QUOTIENT) = true;
            ++i;
            files.at(QUOTIENT) = argv[i];
        }
        if(strcmp(argv[i],"-verificator") == 0) {
            flags.at(VERIFICATOR) = true;
        }
    }
}


int main(int argc, char** argv) {

    //chain-partial-gl-quotient
    std::vector<std::string> files(4,"");
    
    //chain-partial-gl-quotient-verificator
    std::vector<bool> flags(5,false);    
    
    parse_flags(argc, argv, files, flags);
    //input-chain-partial-gl-quotient

    std::string regexp = "";
    char tmp = ' ';
    while(std::cin >> tmp)
        regexp.append(1, tmp);    

    std::vector<int> symbols_amount(4,0);
    for(auto symbol : regexp) {
        if(symbol == '+') symbols_amount.at(SUM) += 1;
        if(symbol == '?') symbols_amount.at(QUESTION) += 1;
        if(symbol == '|') symbols_amount.at(BAR) += 1;
        if(symbol == '*') symbols_amount.at(STAR) += 1;
    }
    
    NFA* glushkov_automaton = compute_glushkov_automaton(regexp, 128, false, false);
    Graph_h g = glushkov_automaton->create_graph();    
    
    PartialOrder preorder(g);

    Graph_h quotient = compute_quotient(g, preorder).first;

    if(flags.at(GL)) {
        //gl file with dot format
        
        g.storeGraphFile("glushkov", files.at(GL));
    }

    if(flags.at(QUOTIENT)) {
        //quotient
        //TODO change name for the node with the set of the original nodes
        quotient.storeGraphFile("quotient", files.at(QUOTIENT));
    }

    //Compute chain decomposition and if file is defined, it will be printed inside file
    int width = solve_mpc(preorder.getTransitiveReduction(), files.at(CHAIN));

    if(flags.at(PARTIAL))
        preorder.printTransitiveReduction(files.at(PARTIAL));

    std::cout << "Regexp length: " << regexp.size() << std::endl;
    std::cout << "+ symbols occurrences: " << symbols_amount.at(SUM) << std::endl;
    std::cout << "? symbols occurrences: " << symbols_amount.at(QUESTION) << std::endl;
    std::cout << "| symbols occurrences: " << symbols_amount.at(BAR) << std::endl;
    std::cout << "* symbols occurrences: " << symbols_amount.at(STAR) << std::endl;
    std::cout << "--------------------------------" << std::endl;
    
    if(flags.at(VERIFICATOR)) {
        auto orders_checks = check_orders(g, preorder);
        std::cout << "co_lex order: ";
        if(orders_checks.first)
            std::cout << "true" <<std::endl;
        else
            std::cout << "false" <<std::endl;

        std::cout << "partial order: ";
        if(orders_checks.second)
            std::cout << "true" <<std::endl;
        else
            std::cout << "false" <<std::endl;
        
        std::cout << "--------------------------------" << std::endl;
    }

    std::cout << "Width: " << width << std::endl;
    std::cout << "Glushkov_nodes: " << (int) glushkov_automaton->no_nodes() << std::endl;
    std::cout << "Glushkov_edges: " << (int) glushkov_automaton->no_edges() << std::endl;
    std::cout << "Quotient_graph_nodes: "<< quotient.getVertexesSize() << std::endl;  
    std::cout << "Quotient_graph_edges: "<< quotient.getEdgesSize() << std::endl;

    //a(a|(ab))b*


    return 0;
}

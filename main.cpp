#include <iostream>
#include <string>
#include <vector>

#include "internal/graph/graph.hpp"
#include "internal/partialOrder.hpp"
#include "internal/verificator.hpp"
#include "internal/mpc.hpp"
#include "internal/parser.hpp"
#include "internal/conversion/nfa.hpp"
#include "internal/conversion/glushkov-automaton.hpp"


#define SUM 0
#define QUESTION 1
#define BAR 2
#define STAR 3

Graph_T<std::string> read_NFA() {
    std::vector<Edge_T<std::string>> edges;	
    std::string dump = "";
    int n = 0;

    //read "digraph"
    std::cin >> dump;
    
    //read name
    std::cin >> dump;

    //read "{"
    std::cin >> dump;
        
    bool finish = false;

    while(!finish) {
        std::cin >> dump;
        //std::cout << dump << std::endl;
        
        if(dump == "}") {
            //last character
            finish = true;
        } else {
            //read the edge

            //source node
            int s = std::stoi(dump), d = 0;
            
            
            //read arrow + destination node
            std::cin >> dump >> d;

            //read label for edge
            bool stop_label = false;
            std::string label= "";

            //read [ label = 
            std::cin >> dump >> dump >> dump >> dump;
            //std::cout << dump << std::endl;

            std::string tmp = "";
            std::string doubleQuote = "\"";
            while(!stop_label) {
                std::cin >> tmp;
                //std::cout << tmp << std::endl;
                //READ LABEL AND COMPARE


                if(tmp == doubleQuote) 
                    stop_label = true;
                else  {
                    label.append(tmp);
                    label.append(" ");
                }
                    
            }
            label.pop_back();

            std::cin >> dump;
            Edge_T<std::string> e(s,d,label);
            edges.push_back(e);
            int max_value = std::max(s,d);
            n = std::max(n,max_value);
        }
    }
    Graph_T<std::string> g(n+1, edges, "");
    return g;
}

void NFA_case(Flags flags) {
    Graph_T<std::string> G = read_NFA();

    Order preorder(G);
    G.printGraph();
    G.printGraphHashed();
    preorder.printIncidenceMatrix();

    auto quotient_pair = compute_quotient(G, preorder);

    auto quotient = quotient_pair.first;
    auto partial_order = quotient_pair.second;
    int width = solve_mpc(partial_order, flags.chain_file);

    if(flags.quotient_file != "") {
        //quotient
        //TODO change name for the node with the set of the original nodes
        quotient.storeGraphFile("quotient", flags.quotient_file);
    }

    //Compute chain decomposition and if file is defined, it will be printed inside file
    if(flags.partial_file != "")
        preorder.printTransitiveReduction(flags.partial_file);


    if(flags.verificator) {
        auto orders_checks = check_orders(quotient_pair);
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
    std::cout << "Original_nodes: " << G.getVertexesSize() << std::endl;
    std::cout << "Original_edges: " << G.getEdgesSize() << std::endl;
    std::cout << "Quotient_graph_nodes: "<< quotient.getVertexesSize() << std::endl;  
    std::cout << "Quotient_graph_edges: "<< quotient.getEdgesSize() << std::endl;
}

void REG_case(Flags flags) {
    std::string regexp = "";
    std::getline(std::cin, regexp);

    // Remove spaces from the string using erase-remove idiom
    regexp.erase(std::remove(regexp.begin(), regexp.end(), ' '), regexp.end());

    std::vector<int> symbols_amount(4,0);
    int l = 0;
    for(auto symbol : regexp) {
        if(symbol == '+') symbols_amount.at(SUM) += 1;
        if(symbol == '?') symbols_amount.at(QUESTION) += 1;
        if(symbol == '|') symbols_amount.at(BAR) += 1;
        if(symbol == '*') symbols_amount.at(STAR) += 1;
        if(symbol >= 'a' && symbol <= 'z') ++l;
    }
    
    NFA* glushkov_automaton = compute_glushkov_automaton(regexp, 128, false, false);
    Graph_T<char> G = glushkov_automaton->create_graph();    
    
    Order preorder(G);

    auto quotient_pair = compute_quotient(G, preorder);
    
    auto quotient = quotient_pair.first;
    auto partial_order = quotient_pair.second;

    int width = solve_mpc(partial_order, flags.chain_file);

    if(flags.quotient_file != "") {
        //quotient
        //TODO change name for the node with the set of the original nodes
        quotient.storeGraphFile("quotient", flags.quotient_file);
    }

    //Compute chain decomposition and if file is defined, it will be printed inside file
    if(flags.partial_file != "")
        preorder.printTransitiveReduction(flags.partial_file);


    

    std::cout << "Regexp length: " << l << std::endl;
    std::cout << "+ symbols occurrences: " << symbols_amount.at(SUM) << std::endl;
    std::cout << "? symbols occurrences: " << symbols_amount.at(QUESTION) << std::endl;
    std::cout << "| symbols occurrences: " << symbols_amount.at(BAR) << std::endl;
    std::cout << "* symbols occurrences: " << symbols_amount.at(STAR) << std::endl;
    std::cout << "--------------------------------" << std::endl;
    
    if(flags.verificator) {
        auto orders_checks = check_orders(quotient_pair);
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
}

int main(int argc, char** argv) {
    
    Flags flags(argc,argv);
    /* std::cout << "type: " << f.type << std::endl;
    std::cout << "chain: " << f.chain_file << std::endl;
    std::cout << "partial: " << f.partial_file << std::endl;
    std::cout << "gl: " << f.gl_file << std::endl;
    std::cout << "quotient: " << f.quotient_file << std::endl;
    std::cout << "v: " << f.verificator << std::endl;
 */
    if(flags.type == "NFA") {
        NFA_case(flags);
    } else if(flags.type == "REG") {
        REG_case(flags);
    }
}
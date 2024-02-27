#ifndef PARSE_HPP
#define PARSE_HPP

#include <string>
#include <cstring>
#include <cassert>
#include <iostream>


struct Flags {

    public:
        std::string type = "";
        std::string chain_file = "";
        std::string partial_file = "";
        std::string gl_file = "";
        std::string quotient_file = "";
        bool verificator = false;

        Flags(int argc, char** argv){           
            bool problem = false;

            for(size_t i = 1; i < argc; ++i) {
                if(strcmp(argv[i],"-NFA") == 0) {
                    if(this->type == "")
                        type = "NFA";
                    else 
                        problem = true;
                }
                if(strcmp(argv[i],"-REG") == 0) {
                    if(this->type == "")
                        type = "REG";
                    else 
                        problem = true;
                }
                if(strcmp(argv[i],"-verificator") == 0) {
                        this->verificator = true;
                }
            }
            if(this->type == "") {
                std::cout << "Need to specify a flag between -NFA and -REG" << std::endl;
            }
            if(this->type == "NFA") {
                for (size_t i = 1; i < argc; i++) {
                    if(strcmp(argv[i],"-chain") == 0) {
                        this->chain_file = argv[i+1];
                    }
                    if(strcmp(argv[i],"-gl") == 0) {
                        std::cout<<"You cannot use flag -gl with a NFA as input." << std::endl;  
                        exit(0);
                    }                    
                    if(strcmp(argv[i],"-partial") == 0) {
                        this->partial_file = argv[i+1];
                    }
                    if(strcmp(argv[i],"-quotient") == 0) {
                        this->quotient_file = argv[i+1];
                    }
                }
            } else {
                if(this->type == "REG") {
                    for (size_t i = 1; i < argc; i++) {
                        if(strcmp(argv[i],"-chain") == 0) {
                            this->chain_file = argv[i+1];
                        }
                        if(strcmp(argv[i],"-gl") == 0) {
                            this->gl_file = argv[i+1];
                        }                    
                        if(strcmp(argv[i],"-partial") == 0) {
                            this->partial_file = argv[i+1];
                        }
                        if(strcmp(argv[i],"-quotient") == 0) {
                            this->quotient_file = argv[i+1];
                        }
                    }
                }   
            }
        }
};

#endif
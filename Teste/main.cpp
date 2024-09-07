#include <iostream>
#include <fstream>

#include "scanner.h"

int main(int argc, char * argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);

    if(!file.is_open()) {
        std::cerr << "failed to open fil: " << argv[1] << std::endl;
        return 1;
    }

    Scanner scanner;
    scanner.switch_streams(file, std::cout);
    std::vector<alpha_token_t> tokens;
    scanner.alpha_yylex(tokens);

    for(auto token : tokens) {
        std::cout << token << std::endl;
    }

    return 0;
}


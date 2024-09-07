#include "../basic.h"
#include "lex.yy.c"

namespace lex {
    std::vector<lex::token> scan(std::string input) {
        yyin = fopen(input.data(), "r");
        std::vector<lex::token> tokens;
        ::scan(tokens);
        return tokens;
    }
}
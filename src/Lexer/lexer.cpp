#include "../basic.h"
#include "lex.yy.c"

namespace lex {
    std::deque<lex::token> scan(const std::string &input) {
        yyin = fopen(input.data(), "r");
        std::deque<lex::token> tokens;
        ::scan(tokens);
        return tokens;
    }
}
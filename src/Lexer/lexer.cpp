#include "../basic.h"
#include "lex.yy.c"

namespace lex {
    std::deque<lex::token> scan(const std::string &input) {
        yyin = fopen(input.data(), "r");
        std::deque<lex::token> tokens;
        ::scan(tokens);
        for(const auto& tk : tokens) {
            if(tk.type.pattern == Type::pattern::ERROR) {
                throw compiler::Exception(compiler::exception::LEXICAL, tk.value);
            }
        }
        return tokens;
    }
}
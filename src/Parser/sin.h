#ifndef COMPILADORES_SIN_H
#define COMPILADORES_SIN_H

#include "../basic.h"
#include "../Lexer/lex.h"
#include "../Parser/AST/ast.h"

namespace sin {

    class cursor {
    public:
        unsigned i = 0;
        std::deque<lex::token> tokens;

        explicit cursor(const std::deque<lex::token> &tokens) : tokens(tokens) {}

        lex::token token() {
            return tokens[i];
        }

        lex::token previous() {
            return tokens[i - 1];
        }
        
        void next() {
            i++;
        }
    };

    ast::Node* parse(cursor & cursor);

    std::string tab(const int i) {
        return std::string(i * 3, ' ');
    }

    void exploreRecursion(const ast::Node* node, const int i = 0) {
        for(int j = 0; j < size(node->tokens); j++) {
            const auto n = node->tokens[j];
            std::cout << std::endl << tab(i) << "[(" << std::to_string(i) << ":" << std::to_string(j) << "):" << n->type.asString() << ", " << n->value << "]";
            exploreRecursion(n, i + 1);
        }
    }

    void explore(ast::Node* node, const int i = 0) {
        std::cout << std::endl << tab(i) << "[(0:0):" << node->type.asString() << ", " << node->value << "]";
        exploreRecursion(node, i + 1);
    }
}

#endif

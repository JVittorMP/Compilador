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

    void exploreRecursion(std::ofstream & file, const ast::Node* node, const int i = 0) {
        for(int j = 0; j < size(node->tokens); j++) {
            const auto n = node->tokens[j];
            file << std::format("{}{}[({}:{}):{}, {}]", '\n', tab(i), i, j, lex::name(n->pattern), n->value, n->line);
            exploreRecursion(file, n, i + 1);
        }
    }

    void explore(std::ofstream & file, ast::Node* node, const int i = 0) {
        file << std::format("{}[(0:0):{}, {}]", tab(i), lex::name(node->pattern), node->value, node->line);
        exploreRecursion(file, node, i + 1);
    }

    void outputRecursion(const ast::Node* node, const int i = 0) {
        for(int j = 0; j < size(node->tokens); j++) {
            const auto n = node->tokens[j];
            std::cout << std::format("{}{}[({}:{}):{}, {}]", '\n', tab(i), i, j, lex::name(n->pattern), n->value, n->line);
            outputRecursion(n, i + 1);
        }
    }

    void output(ast::Node* node, const int i = 0) {
        std::cout << std::endl << std::endl <<  std::format("{}[(0:0):{}, {}]", tab(i), lex::name(node->pattern), node->value, node->line);
        outputRecursion(node, i + 1);
        std::cout.flush();
    }
}

#endif

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

    int PROG(ast::Node* node, cursor & cursor);
    int INIT(ast::Node* node, cursor & cursor);
    int METODO(ast::Node* node, cursor & cursor);
    int PARAMS(ast::Node* node, cursor & cursor);
    int MAIS_PARAMS(ast::Node* node, cursor & cursor);
    int DC(ast::Node* node, cursor & cursor);
    int MAIS_DC(ast::Node* node, cursor & cursor);
    int VAR(ast::Node* node, cursor & cursor);
    int VARS(ast::Node* node, cursor & cursor);
    int MAIS_VAR(ast::Node* node, cursor & cursor);
    int TIPO(ast::Node* node, cursor & cursor);
    int CMDS(ast::Node* node, cursor & cursor);
    int CONDITIONAL_CMD(ast::Node* node, cursor & cursor);
    int CMD(ast::Node* node, cursor & cursor);
    int PFALSA(ast::Node* node, cursor & cursor);
    int RESTO_IDENT(ast::Node* node, cursor & cursor);
    int LISTA_ARG(ast::Node* node, cursor & cursor);
    int ARGUMENTOS(ast::Node* node, cursor & cursor);
    int MAIS_IDENT(ast::Node* node, cursor & cursor);
    int EXP_IDENT(ast::Node* node, cursor & cursor);
    int CONDICAO(ast::Node* node, cursor & cursor);
    int RELACAO(ast::Node* node, cursor & cursor);
    int EXPRESSAO(ast::Node* node, cursor & cursor);
    int TERMO(ast::Node* node, cursor & cursor);
    int OP_UN(ast::Node* node, cursor & cursor);
    int FATOR(ast::Node* node, cursor & cursor);
    int OUTROS_TERMOS(ast::Node* node, cursor & cursor);
    int OP_AD(ast::Node* node, cursor & cursor);
    int MAIS_FATORES(ast::Node* node, cursor & cursor);
    int OP_MUL(ast::Node* node, cursor & cursor);

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

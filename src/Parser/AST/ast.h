#ifndef COMPILADORES_AST_H
#define COMPILADORES_AST_H

#include <utility>

#include "../../basic.h"
#include "../../Lexer/lex.h"

namespace ast {

    class Node {
    public:
        lex::Type type;
        std::string value;
        unsigned line = 0;
        std::deque<Node*> tokens;

        Node() = default;
        explicit Node(lex::Type type):
            type(type), value(type.asValue()) {}
        Node(lex::Type type, std::string value):
            type(type), value(std::move(value)) {}
        explicit Node(lex::token t):
            type(t.type), value(t.value), line(t.linha) {}

        static Node* pointer(lex::Type type, std::string value) {
            return new Node(type, std::move(value));
        }

        static Node* pointer(lex::Type type) {
            return new Node(type);
        }

        static Node* pointer(lex::token t) {
            return new Node(std::move(t));
        }

        bool operator==(const Node* & node) const {
            return std::tie(this->type, this->value) == std::tie(node->type, node->value);
        }
    };

    void PROG(Node* node, std::vector<lex::token>::iterator & token);
    void INIT(Node* node, std::vector<lex::token>::iterator & token);
    void METODO(Node* node, std::vector<lex::token>::iterator & token);
    void PARAMS(Node* node, std::vector<lex::token>::iterator & token);
    void MAIS_PARAMS(Node* node, std::vector<lex::token>::iterator & token);
    void DC(Node* node, std::vector<lex::token>::iterator & token);
    void MAIS_DC(Node* node, std::vector<lex::token>::iterator & token);
    void VAR(Node* node, std::vector<lex::token>::iterator & token);
    void VARS(Node* node, std::vector<lex::token>::iterator & token);
    void MAIS_VAR(Node* node, std::vector<lex::token>::iterator & token);
    void TIPO(Node* node, std::vector<lex::token>::iterator & token);
    void CMDS(Node* node, std::vector<lex::token>::iterator & token);
    void CONDITIONAL_CMD(Node* node, std::vector<lex::token>::iterator & token);
    void CMD(Node* node, std::vector<lex::token>::iterator & token);
    void PFALSA(Node* node, std::vector<lex::token>::iterator & token);
    void RESTO_IDENT(Node* node, std::vector<lex::token>::iterator & token);
    void LISTA_ARG(Node* node, std::vector<lex::token>::iterator & token);
    void ARGUMENTOS(Node* node, std::vector<lex::token>::iterator & token);
    void MAIS_IDENT(Node* node, std::vector<lex::token>::iterator & token);
    void EXP_IDENT(Node* node, std::vector<lex::token>::iterator & token);
    void CONDICAO(Node* node, std::vector<lex::token>::iterator & token);
    void RELACAO(Node* node, std::vector<lex::token>::iterator & token);
    void EXPRESSAO(Node* node, std::vector<lex::token>::iterator & token);
    void TERMO(Node* node, std::vector<lex::token>::iterator & token);
    void OP_UN(Node* node, std::vector<lex::token>::iterator & token);
    void FATOR(Node* node, std::vector<lex::token>::iterator & token);
    void OUTROS_TERMOS(Node* node, std::vector<lex::token>::iterator & token);
    void OP_AD(Node* node, std::vector<lex::token>::iterator & token);
    void MAIS_FATORES(Node* node, std::vector<lex::token>::iterator & token);
    void OP_MUL(Node* node, std::vector<lex::token>::iterator & token);

    Node* buildParseTree(std::vector<lex::token>::iterator & token);
}

#endif

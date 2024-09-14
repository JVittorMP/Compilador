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
        explicit Node(const lex::token& t):
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
}

#endif

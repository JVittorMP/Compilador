#ifndef COMPILADORES_AST_H
#define COMPILADORES_AST_H

namespace ast {

    class Node {
    public:
        lex::pattern pattern = lex::VAZIO;
        std::string value;
        unsigned line = 0;
        std::deque<Node*> tokens;

        Node() = default;
        explicit Node(lex::pattern type): pattern(type), value(lex::value(pattern)) {}
        explicit Node(const lex::token & t): pattern(t.pattern), value(t.value), line(t.linha) {}
        Node(const lex::pattern type, std::string value):
                pattern(type), value(std::move(value)) {}
        Node(const lex::pattern type, std::string value, unsigned line):
                pattern(type), value(std::move(value)), line(line) {}


        static Node* pointer(lex::pattern type, std::string value, unsigned line) {
            return new Node(type, std::move(value), line);
        }

        static Node* pointer(lex::pattern type, std::string value) {
            return new Node(type, std::move(value));
        }

        static Node* pointer(lex::pattern type) {
            return new Node(type);
        }

        static Node* pointer(const lex::token & t) {
            return new Node(t);
        }

        bool operator==(const Node* & node) const {
            return std::tie(this->pattern, this->value) == std::tie(node->pattern, node->value);
        }

        Node* operator [](int x) {
            return tokens[x];
        }
    };

}

#endif

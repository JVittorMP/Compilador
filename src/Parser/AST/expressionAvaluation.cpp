namespace exp {
    bool isNumber(std::string s) {
        if (s.empty()) return false;
        if (size(s) > 1 && (s[0] == '-' || s[0] == '+')) s = std::string(s.begin() + 1, s.end());
        if (std::ranges::all_of(s, [](const char c) { return isdigit(c); })) return true;
        return false;
    }

    bool isOperand(const char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    bool isOperand(const std::string & s) {
        if (size(s) != 1) return false;
        return isOperand(s[0]);
    }

    int priority(const char nd) {
        if (nd == '$') return 5;
        if (nd == '*' || nd == '/') return 4;
        if (nd == '+' || nd == '-') return 3;
        if (nd == '(') return 2;
        return 0;
    }

    int priority(const char c1, const char c2) {
        return priority(c1) >= priority(c2);
    }

    int priority(const std::string & s1, const std::string & s2) {
        if (size(s1) != 1 || size(s2) != 1) return 0;
        return priority(s1[0], s2[0]);
    }

    ast::Node* pop(std::stack<ast::Node*> &nodes) {
        ast::Node *node = nodes.top();
        nodes.pop();
        return node;
    }

    void push(std::stack<ast::Node*> & nodes, std::stack<ast::Node*> & ops) {
        auto op = pop(ops);
        auto node = ast::Node::pointer(op->type, op->value, op->line);
        node->tokens.push_back(pop(nodes));
        node->tokens.push_back(pop(nodes));
        if(node->type.pattern == lex::pattern::OP_UN) {
            node->tokens.pop_back();
            node->value = lex::Type::asValue(lex::pattern::SUBTRACAO);
        }
        nodes.push(node);
    }

    ast::Node* buildTree(const std::deque<ast::Node *> & entries) {
        std::stack<ast::Node*> nodes;
        std::stack<ast::Node*> ops;

        for(const auto & nd: entries) {
            if(nd->value == "(") {
                ops.push(nd);
            } else if (nd->type.pattern == lex::pattern::NUM || nd->type.pattern == lex::pattern::IDENTIFIER) {
                nodes.push(nd);
            } else if (isOperand(nd->value)) {
                if(nd->type.pattern == lex::pattern::OP_UN) nd->value = "$";
                if(nd->type.pattern == lex::pattern::OP_UN) nodes.push(ast::Node::pointer(lex::Type(lex::pattern::NUM), "0"));
                while (!ops.empty() && ops.top()->value != "(" && priority(ops.top()->value, nd->value)) {
                    push(nodes, ops);
                }
                ops.push(nd);
            } else if(nd->value == ")") {
                while (!ops.empty() && ops.top()->value != "(") {
                    push(nodes, ops);
                }
                ops.pop();
            }
        }
        while (!ops.empty()) {
            push(nodes, ops);
        }
        return nodes.top();
    }
}
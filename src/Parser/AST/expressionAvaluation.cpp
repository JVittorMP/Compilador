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
        if (nd == '*' || nd == '/') return 2;
        if (nd == '+' || nd == '-') return 1;
        return 0;
    }

    int priority(const char c1, const char c2) {
        return priority(c1) >= priority(c2);
    }

    int priority(const std::string & s1, const std::string & s2) {
        if (size(s1) != 1 || size(s2) != 1) return 0;
        return priority(s1[0], s2[0]);
    }

    std::string pop(std::stack<std::string> &ops) {
        const std::string op = ops.top();
        ops.pop();
        return op;
    }

    ast::Node* pop(std::stack<ast::Node*> &nodes) {
        ast::Node *node = nodes.top();
        nodes.pop();
        return node;
    }

    ast::Node* buildTree(const std::deque<ast::Node *> &entries) {
        std::stack<ast::Node *> nodes;
        std::stack<std::string> ops;

        for (const auto &nd: entries) {
            if (isNumber(nd->value) || !isOperand(nd->value)) {
                nodes.push(nd);
            } else if (isOperand(nd->value)) {
                while (!ops.empty() && priority(ops.top(), nd->value)) {
                    auto node = ast::Node::pointer(lex::Type(lex::Type::pattern::OPERATOR), pop(ops));
                    node->tokens.push_back(pop(nodes));
                    node->tokens.push_back(pop(nodes));
                    nodes.push(node);
                }
                ops.push(nd->value);
            }
        }
        while (!ops.empty()) {
            auto node = ast::Node::pointer(lex::Type(lex::Type::pattern::OPERATOR), pop(ops));
            node->tokens.push_back(pop(nodes));
            node->tokens.push_back(pop(nodes));
            nodes.push(node);
        }
        return nodes.top();
    }
}
#include "../../basic.h"
#include "ast.h"
//#include "abstractSyntaxTree.cpp"

bool isNumber(std::string s) {
    if(s.empty() ) return false;
    if(size(s) > 1 && (s[0] == '-' || s[0] == '+')) s = std::string(s.begin() + 1, s.end());
    if(std::all_of(s.begin(), s.end(), [](char c) {return isdigit(c);})) return true;
    return false;
}

bool isOperand(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isOperand(const std::string & s) {
    if(size(s) != 1) return false;
    return isOperand(s[0]);
}

int priority(char nd) {
    if(nd == '*' || nd == '/') return 2;
    if(nd == '+' || nd == '-') return 1;
    return 0;
}

int priority(char c1, char c2) {
    return priority(c1) >= priority(c2);
}

int priority(const std::string & s1, const std::string & s2) {
    if(size(s1) != 1 || size(s2) != 1) return 0;
    return priority(s1[0], s2[0]);
}

std::string pop(std::stack<std::string> & ops) {
    const std::string op = ops.top();
    ops.pop();
    return op;
}

char pop(std::stack<char> & ops) {
    const char op = ops.top();
    ops.pop();
    return op;
}

ast::Node* pop(std::stack<ast::Node*> & nodes) {
    ast::Node* node = nodes.top();
    nodes.pop();
    return node;
}

ast::Node* buildTree(const std::string & s) {
    std::stack<ast::Node*> nodes;
    std::stack<char> ops;

    for(const auto & nd : s) {
        if(isdigit(nd)) {
            nodes.push(new ast::Node({"Num", std::string(1, nd), true}));
        } else if(isOperand(nd)) {
            while(!ops.empty() && priority(ops.top(), nd)) {
                auto node = new ast::Node({"Operator", std::string(1, pop(ops)), true});
                node->tokens.push_back(pop(nodes));
                node->tokens.push_back(pop(nodes));
                nodes.push(node);
            }
            ops.push(nd);
        }
    }
    while(!ops.empty()) {
        auto node = new ast::Node({"Operator", std::string(1, pop(ops)), true});
        node->tokens.push_back(pop(nodes));
        node->tokens.push_back(pop(nodes));
        nodes.push(node);
    }
    return nodes.top();
}

ast::Node* buildTree2(const std::deque<ast::Node*>& entries) {
    std::stack<ast::Node*> nodes;
    std::stack<std::string> ops;

    for(const auto & nd : entries) {
        if(isNumber(nd->value) || !isOperand(nd->value)) {
            nodes.push(nd);
        } else if(isOperand(nd->value)) {
            while(!ops.empty() && priority(ops.top(), nd->value)) {
                auto node = new ast::Node({"Operator", pop(ops), true});
                node->tokens.push_back(pop(nodes));
                node->tokens.push_back(pop(nodes));
                nodes.push(node);
            }
            ops.push(nd->value);
        }
    }
    while(!ops.empty()) {
        auto node = new ast::Node({"Operator", pop(ops), true});
        node->tokens.push_back(pop(nodes));
        node->tokens.push_back(pop(nodes));
        nodes.push(node);
    }
    return nodes.top();
}

//int structureExpression() {
//    std::string s = "2*3-6/6*2+5";
//    ast::Node* root = buildTree(s);
//    std::cout << "[(0,0):" << root->type << ", " << root->value << "]";
//    explore02(root, 1);
//    return 0;
//}
//
//int structureExpression(const std::deque<ast::Node*> & nodes) {
//    buildTree2(nodes);
//    ast::Node* root = buildTree2(nodes);
//    std::cout << "[(0,0):" << root->type << ", " << root->value << "]";
//    explore02(root, 1);
//    return 0;
//}
//
//int main() {
//    std::deque<ast::Node*> nodes;
//    nodes.push_back(new ast::Node("Num", "-2", true));
//    nodes.push_back(new ast::Node("Operator", "*", true));
//    nodes.push_back(new ast::Node("Num", "3", true));
//    nodes.push_back(new ast::Node("Operator", "-", true));
//    nodes.push_back(new ast::Node("Num", "6", true));
//    nodes.push_back(new ast::Node("Operator", "/", true));
//    nodes.push_back(new ast::Node("Num", "6", true));
//    nodes.push_back(new ast::Node("Operator", "*", true));
//    nodes.push_back(new ast::Node("Num", "2", true));
//    nodes.push_back(new ast::Node("Operator", "+", true));
//    nodes.push_back(new ast::Node("Num", "5", true));
//    nodes.push_back(new ast::Node("Operator", "-", true));
//    nodes.push_back(new ast::Node("Num", "-b", true));
//    structureExpression();
//    std::cout << std::endl << std::endl;
//    structureExpression(nodes);
//    return 0;
//}
#include "../../basic.h"
#include "../AST/ast.h"

// Métodos que solucionam árvores de expresão e retornam o valor
double resolveExpresion(ast::Node* node) {
    return 0;
}


// Métodos para construir a árvore de expressões
bool isNumber(std::string s) {
    if(s.empty()) return false;
    if(size(s) > 1 && (s[0] == '-' || s[0] == '+')) s = std::string(s.begin() + 1, s.end());
    if(std::ranges::all_of(s, [](const char c) {return isdigit(c);})) return true;
    return false;
}

bool isOperand(const char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isOperand(const std::string & s) {
    if(size(s) != 1) return false;
    return isOperand(s[0]);
}

int priority(const char nd) {
    if(nd == '*' || nd == '/') return 2;
    if(nd == '+' || nd == '-') return 1;
    return 0;
}

int priority(const char c1, const char c2) {
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

ast::Node* pop(std::stack<ast::Node*> & nodes) {
    ast::Node* node = nodes.top();
    nodes.pop();
    return node;
}
ast::Node* buildTree(const std::deque<ast::Node*>& entries) {
    std::stack<ast::Node*> nodes;
    std::stack<std::string> ops;

    for(const auto & nd : entries) {
        if(isNumber(nd->value) || !isOperand(nd->value)) {
            nodes.push(nd);
        } else if(isOperand(nd->value)) {
            while(!ops.empty() && priority(ops.top(), nd->value)) {
                auto node = ast::Node::pointer(lex::Type(lex::Type::pattern::OPERATOR), pop(ops));
                node->tokens.push_back(pop(nodes));
                node->tokens.push_back(pop(nodes));
                nodes.push(node);
            }
            ops.push(nd->value);
        }
    }
    while(!ops.empty()) {
        auto node = ast::Node::pointer(lex::Type(lex::Type::pattern::OPERATOR), pop(ops));
        node->tokens.push_back(pop(nodes));
        node->tokens.push_back(pop(nodes));
        nodes.push(node);
    }
    return nodes.top();
}

std::deque<ast::Node*> getExpression(std::deque<ast::Node*> v, ast::Node* & cur);
void simplifyExpression(ast::Node* node, std::deque<ast::Node*> & exp);

void explore(ast::Node* node, int i = 0) {
    std::cout << std::endl << ((node->value.empty()) ? "@" : tab(i) + std::to_string(i) + " " + node->value) << " ";
    for(int j = 0; j < size(node->tokens); j++) {
        auto n = node->tokens[j];
        if(n->tokens.empty()) std::cout << ((n->value.empty()) ? "@" : n->value) << " ";
        else {
            explore(n, i + 1);
            //if(j != size(node->tokens) - 1) std::cout << std::endl << tab(i) + std::to_string(i) + " ";
        }
    }
}

void exploreT(ast::Node* node, int i = 0) {
    for(int j = 0; j < size(node->tokens); j++) {
        auto n = node->tokens[j];
        std::cout << std::endl << tab(i) << "[(" << std::to_string(i) << ":" << std::to_string(j) << "):" << n->type.asString() << ", " << n->value << "]";
        exploreT(n, i + 1);
    }
}

void explore02(ast::Node* node, int i = 0) {
    std::cout << std::endl << tab(i) << "[(0:0):" << node->type.asString() << ", " << node->value << "]";
    exploreT(node, i + 1);
}

void getVars(std::deque<ast::Node*> & v, ast::Node* cur) {
    if(cur->tokens.empty()) return;
    for(auto n : cur->tokens) {
        if(n->type.pattern == lex::Type::pattern::IDENTIFIER) v.push_back(n);
        getVars(v, n);
    }
}

void getDeclarations(std::deque<ast::Node*> & dc, ast::Node* cur) {
    if(cur->tokens.empty()) return;
    for(auto n : cur->tokens) {
        if(n->type.pattern == lex::Type::pattern::VAR) {
            for(auto b : n->tokens) {
                if(b->type.pattern == lex::Type::pattern::VARS) {
                    std::deque<ast::Node*> vars;
                    getVars(vars, b);
                    b->tokens = vars;
                }
            }
            dc.push_back(n);
        } else {
            getDeclarations(dc, n);
        }

    }
}

void getCmds(std::deque<ast::Node*> & cmds, ast::Node* cur) {
    if(cur->tokens.empty()) return;
    for(auto & n : cur->tokens) {
        if(n->type.pattern == lex::Type::pattern::CMD || n->type.pattern == lex::Type::pattern::CONDITIONAL_CMD) {
            if(n->tokens[0]->value == lex::Type::asValue(lex::Type::pattern::OUTPUT)) {
                std::deque<ast::Node*> subs;
                for(auto nd : n->tokens) {
                    if(!nd->type.status() || nd->value == lex::Type::asValue(lex::Type::pattern::OUTPUT)) subs.push_back(nd);
                }
                n->tokens = subs;
            }
            cmds.push_back(n);
        } else {
            getCmds(cmds, n);
        }

    }
}

void avaluateNegNum(ast::Node* & cur) {
    if(cur->tokens.empty()) return;
    for(auto & nd : cur->tokens) {
        if(nd->type.pattern == lex::Type::pattern::TERMO) {
            if(nd->tokens[0]->type.pattern == lex::Type::pattern::OP_UN) {
                std::string s = "-" + nd->tokens[1]->tokens[0]->value;
                nd->tokens[1]->tokens[0]->value = s;
                nd->tokens.pop_front();
            }
            nd->tokens[0] = nd->tokens[0]->tokens[0];
        }
        avaluateNegNum(nd);
    }
}

ast::Node* changeExpressionNode(ast::Node* ex) {
    std::deque<ast::Node*> v;
    avaluateNegNum(ex);
    ast::Node* exCpy = ex;
    simplifyExpression(exCpy, v);
    exCpy = buildTree(v);
    ex->tokens.clear();
    ex->tokens.push_back(exCpy);
    return ex;
}

void orderAtribution(ast::Node* & node) {
    ast::Node* & id = node->tokens[0];
    ast::Node* & ri = node->tokens[1];
    ast::Node* & op = ri->tokens[0];
    ast::Node* & ex = ri->tokens[1]->tokens[0];

    if(ex->type.pattern != lex::Type::pattern::INPUT) ex = changeExpressionNode(ex);

    auto* novo = ast::Node::pointer(op->type, op->value);
    novo->tokens.push_back(id);
    novo->tokens.push_back(ex);

    id = novo;
    node->tokens.pop_back(); // Retirar "REST_IDENT do final de Node(CMD)"
}

void simplifyExpression(ast::Node* node, std::deque<ast::Node*> & exp) {
    for(auto nd : node->tokens) {
        if(nd->type.pattern == lex::Type::pattern::NUM || nd->type.pattern == lex::Type::pattern::OPERATOR || nd->type.pattern == lex::Type::pattern::IDENTIFIER) exp.push_back(nd);
        simplifyExpression(nd, exp);
    }
}

void orderConditionals(ast::Node* & node) {
    ast::Node* & cond = node->tokens[1];
    ast::Node* & ex1 = cond->tokens[0];
    ast::Node* & ex2 = cond->tokens[2];

    ex1 = changeExpressionNode(ex1);
    ex2 = changeExpressionNode(ex2);
}

void orderOutput(ast::Node* & node) {
    std::deque<ast::Node*> exp;
    ast::Node* & ex = node->tokens[1];
    ex = changeExpressionNode(ex);
    // simplifyExpression(ex, exp);
    // ex->tokens.clear();
    // ex->tokens.push_back(buildTree(exp));
}

void getArguments(ast::Node* & node, std::deque<ast::Node*> & v) {
    for(auto nd : node->tokens) {
        if(nd->type.pattern == lex::Type::pattern::IDENTIFIER) v.push_back(nd);
        getArguments(nd, v);
    }
}

ast::Node* orderArguments(ast::Node* & node) {
    std::deque<ast::Node*> v;
    getArguments(node, v);
    node->tokens = v;
    return node;
}

void filterCmds(ast::Node* & node) {
    for(auto & n : node->tokens) {
        ast::Node* cur = n->tokens.front();
        if(cur->type.pattern == lex::Type::pattern::KEYWORD) {
            if(cur->value == lex::Type::asValue(lex::Type::pattern::OUTPUT)) orderOutput(n);
            if(cur->value == lex::Type::asValue(lex::Type::pattern::IF) || cur->value == lex::Type::asValue(lex::Type::pattern::WHILE)) orderConditionals(n);
        }
        else if(cur->type.pattern == lex::Type::pattern::IDENTIFIER) {
            if(n->tokens[1]->tokens.front()->type.pattern == lex::Type::pattern::OPERATOR) {
                orderAtribution(n);
            } else {
                if(!n->tokens[1]->tokens.empty()) n->tokens[1] = orderArguments(n->tokens[1]->tokens[0]->tokens[0]);
                else n->tokens.pop_back();
            }
        }
    }
}

void getParams(std::deque<ast::Node*> & v, ast::Node* cur) {
    if(cur->tokens.empty()) return;
    auto* last = cur->tokens.back();

    auto* param = ast::Node::pointer(lex::Type(lex::Type::pattern::PARAM));
    param->tokens.push_back(cur->tokens[0]);
    param->tokens.push_back(cur->tokens[1]);
    v.push_back(param);
    if(last->type.pattern == lex::Type::pattern::MAIS_PARAMS) getParams(v, last->tokens.front());
}

void compressSignature(ast::Node* & node) {
    std::deque<ast::Node*> v;
    ast::Node* & params = node->tokens[2];
    getParams(v, params);
    params->tokens = v;
}

void compressReturn(ast::Node* & node) {
    std::deque<ast::Node*> v;
    ast::Node* & exp = node->tokens[1];
    exp = changeExpressionNode(exp);
}

void getMethod(ast::Node* node, std::deque<ast::Node*> & v) {
    auto* signature =  ast::Node::pointer(lex::Type(lex::Type::pattern::SIGNATURE));
    auto* retorno = ast::Node::pointer(lex::Type(lex::Type::pattern::RETURN));
    for(auto & nd : node->tokens) {
        if(nd->type.pattern == lex::Type::pattern::IDENTIFIER) signature->tokens.push_front(nd);
        if(nd->type.pattern == lex::Type::pattern::TIPO || nd->type.pattern == lex::Type::pattern::PARAMS) signature->tokens.push_back(nd);
        if(nd->type.pattern == lex::Type::pattern::DC || nd->type.pattern == lex::Type::pattern::CMDS) v.push_back(nd);
    }
    retorno->tokens.push_back(node->tokens.end()[-2]);
    retorno->tokens.push_back(node->tokens.back());
    if(signature->tokens.size() == 3) compressSignature(signature);
    compressReturn(retorno);
    node->tokens.clear();
    v.push_front(signature);
    v.push_back(retorno);
}

void compressSubTree(const std::string & s, ast::Node* node, std::deque<ast::Node*> & v) {
    if(s == lex::Type::asString(lex::Type::pattern::DC)) getDeclarations(v, node);
    else if(s == lex::Type::asString(lex::Type::pattern::CMDS)) {
        getCmds(v, node);
    }
    else if(s == lex::Type::asString(lex::Type::pattern::METODO)) {
        getMethod(node, v);
    }
}

void compressStructure(ast::Node* & node) {
    if(node->tokens.empty()) return;
    std::deque<ast::Node*> v;
    compressSubTree(node->type.asString(), node, v);
    node->tokens = v;
}

bool isPunctuation(enum lex::Type::pattern p) {
    if( p == lex::Type::pattern::PUNCTUATION ||
        p == lex::Type::pattern::LCHAVE ||
        p == lex::Type::pattern::RCHAVE ||
        p == lex::Type::pattern::LCOLCHETE ||
        p == lex::Type::pattern::RCOLCHETE ||
        p == lex::Type::pattern::LPARENTESE ||
        p == lex::Type::pattern::RPARENTESE ||
        p == lex::Type::pattern::VIRGULA ||
        p == lex::Type::pattern::PONTO_VIRGULA ||
        p == lex::Type::pattern::RPARENTESE
    ) return true;
    return false;
}

void eraseEmptyProductions(ast::Node* & node) {
    for(int i = 0; i < size(node->tokens); i++) {
        ast::Node* n = node->tokens[i];
        if(isPunctuation(n->type.pattern)) {
            node->tokens.erase(node->tokens.begin() + i);
            i--;
            continue;
        }
        if(n->tokens.empty()) continue;
        if(n->tokens[0]->type.pattern == lex::Type::pattern::VAZIO) {
            node->tokens.erase(node->tokens.begin() + i);
            i--;
            continue;
        }
        eraseEmptyProductions(n);
    }
}

void removeInit(ast::Node* & root) {
    auto init = root->tokens[1];

    auto itInit = init->tokens.begin();
    while(itInit != init->tokens.end()) {
        if((*itInit)->type.pattern != lex::Type::pattern::KEYWORD) break;
        init->tokens.erase(itInit);
        itInit++;
    }

    init->value = "public static void main";
}

void compressTest(ast::Node* & node) {
    for(auto & n : node->tokens) {
        if(n->tokens.empty()) continue;
        if(n->type.pattern == lex::Type::pattern::DC) {
            compressStructure(n);
        } else if(n->type.pattern == lex::Type::pattern::CMDS) {
            compressStructure(n);
            filterCmds(n);
        }
        else if(n->type.pattern == lex::Type::pattern::METODO) {
            compressStructure(n);
        }
        compressTest(n);
    }
}

ast::Node* compress(ast::Node* & root) {
    eraseEmptyProductions(root);

    // retirar entradas do programa (public, class)
    root->tokens.pop_front();
    root->tokens.pop_front();

    removeInit(root);
    //exploreNode02(root);
    compressTest(root);
    return root;
}

ast::Node* buildAST(ast::Node* root) {
    return compress(root);
}

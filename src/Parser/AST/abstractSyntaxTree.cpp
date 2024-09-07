#include "ast.h"
#include "expressionAvaluation.cpp"
#include "parseTree.cpp"

std::deque<ast::Node*> getExpression(std::deque<ast::Node*> v, ast::Node* & cur);
void simplifyExpression(ast::Node* node, std::deque<ast::Node*> & exp);

std::string tab(int i) {
    return std::string(i * 3, ' ');
}

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
        std::cout << std::endl << tab(i) << "[(" << std::to_string(i) << ":" << std::to_string(j) << "):" << n->type << ", " << n->value << "]";
        exploreT(n, i + 1);
    }
}

void explore02(ast::Node* node, int i = 0) {
    std::cout << std::endl << tab(i) << "[(0:0):" << node->type << ", " << node->value << "]";
    exploreT(node, i + 1);
}

void getVars(std::deque<ast::Node*> & v, ast::Node* cur) {
    if(cur->tokens.empty()) return;
    for(auto n : cur->tokens) {
        if(n->type == "Identifier") v.push_back(n);
        getVars(v, n);
    }
}

void getDeclarations(std::deque<ast::Node*> & dc, ast::Node* cur) {
    if(cur->tokens.empty()) return;
    for(auto n : cur->tokens) {
        if(n->type == "VAR") {
            for(auto b : n->tokens) {
                if(b->type == "VARS") {
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

// Sem Uso
std::deque<ast::Node*> getTermo(std::deque<ast::Node*> v, ast::Node* & cur) {
    if(cur->tokens[0]->type == "OP_UN") {
        cur->tokens[1]->tokens[0]->value.insert(cur->tokens[1]->tokens[0]->value.begin(), '-');
        cur->tokens.pop_front();
        if(cur->tokens.size() == 2) {
            getExpression(v, cur->tokens[1]);
        }
    }
    cur->tokens[0] = cur->tokens[0]->tokens[0];
    return v;
}

// sem Uso
std::deque<ast::Node*> getExpression(std::deque<ast::Node*> v, ast::Node* & cur) {
    if(cur->tokens.empty()) return v;
    if(cur->type != "EXPRESSION") {
        cur->type = "EXPRESSION";
        cur->value = "EXPRESSION";
    }
    for(auto & nd : cur->tokens) {
        if(nd->type == "TERMO") {
            getTermo(v, nd);
        }
    }
    return v;
}

void turnExp(ast::Node* & cur) {
    cur->type = "EXPRESSION";
    cur->value = "EXPRESSION";
}

void getExp(ast::Node* & cur) {
    //turnExp(cur);
    cur->tokens[0] = cur->tokens[0]->tokens[0];
    cur->tokens[1] = cur->tokens[1]->tokens[0];
    if(cur->tokens.back()->type == "MAIS_FATORES") getExp(cur->tokens.back());
    return;
}

// Sem Uso
void getExpression2(ast::Node* & cur) {
    if(cur->tokens.empty()) return;
    for(auto & nd : cur->tokens) {
        if(nd->type == "TERMO") {
            //turnExp(nd);
            if(nd->tokens[0]->type == "OP_UN") {
                std::string s = "-" + nd->tokens[1]->tokens[0]->value;
                nd->tokens[1]->tokens[0]->value = s;
                nd->tokens.pop_front();
            }
            nd->tokens[0] = nd->tokens[0]->tokens[0];
            if(nd->tokens.back()->type == "MAIS_FATORES") getExp(nd->tokens.back());
        } else if(nd->type == "OUTROS_TERMOS") {
            //turnExp(nd);
            nd->tokens[0] = nd->tokens[0]->tokens[0];
            getExpression2(nd);
        }
    }
    return;
}

void getCmds(std::deque<ast::Node*> & cmds, ast::Node* cur) {
    if(cur->tokens.empty()) return;
    for(auto & n : cur->tokens) {
        if(n->type == "CMD" || n->type == "CONDITIONAL_CMD") {
            if(n->tokens[0]->value == "System.out.println") {
                std::deque<ast::Node*> subs;
                for(auto nd : n->tokens) {
                    if(!nd->terminal || nd->value == "System.out.println") subs.push_back(nd);
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
        if(nd->type == "TERMO") {
            if(nd->tokens[0]->type == "OP_UN") {
                std::string s = "-" + nd->tokens[1]->tokens[0]->value;
                nd->tokens[1]->tokens[0]->value = s;
                nd->tokens.pop_front();
            }
            nd->tokens[0] = nd->tokens[0]->tokens[0];
        }
        avaluateNegNum(nd);
    }
    return;
}

ast::Node* changeExpressionNode(ast::Node* ex) {
    std::deque<ast::Node*> v;
    avaluateNegNum(ex);
    ast::Node* exCpy = ex;
    simplifyExpression(exCpy, v);
    exCpy = buildTree2(v);
    ex->tokens.clear();
    ex->tokens.push_back(exCpy);
    return ex;
}

void orderAtribution(ast::Node* & node) {
    ast::Node* & id = node->tokens[0];
    ast::Node* & ri = node->tokens[1];
    ast::Node* & op = ri->tokens[0];
    ast::Node* & ex = ri->tokens[1]->tokens[0];

    if(ex->type != "Input") ex = changeExpressionNode(ex);

    auto* novo = new ast::Node({op->type, op->value, op->terminal});
    novo->tokens.push_back(id);
    novo->tokens.push_back(ex);

    id = novo;
    node->tokens.pop_back(); // Retirar "REST_IDENT do final de Node(CMD)"
}

void simplifyExpression(ast::Node* node, std::deque<ast::Node*> & exp) {
    for(auto nd : node->tokens) {
        if(nd->type == "Num" || nd->type == "Operator" || nd->type == "Identifier") exp.push_back(nd);
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
    simplifyExpression(ex, exp);
    ex->tokens.clear();
    ex->tokens.push_back(buildTree2(exp));
}

void getArguments(ast::Node* & node, std::deque<ast::Node*> & v) {
    for(auto nd : node->tokens) {
        if(nd->type == "Identifier") v.push_back(nd);
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
        if(cur->type == "Keyword") {
            if(cur->value == "System.out.println") orderOutput(n);
            if(cur->value == "if" || cur->value == "while") orderConditionals(n);
        }
        else if(cur->type == "Identifier") {
            if(n->tokens[1]->tokens.front()->type == "Operator") {
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
    auto* param = new ast::Node("PARAM", "PARAM", false);
    param->tokens.push_back(cur->tokens[0]);
    param->tokens.push_back(cur->tokens[1]);
    v.push_back(param);
    if(last->type == "MAIS_PARAMS") getParams(v, last->tokens.front());
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
    auto* signature = new ast::Node("SIGNATURE", "SIGNATURE", false);
    auto* retorno = new ast::Node("RETURN", "RETURN", false);
    for(auto & nd : node->tokens) {
        if(nd->type == "Identifier") signature->tokens.push_front(nd);
        if(nd->type == "TIPO" || nd->type == "PARAMS") signature->tokens.push_back(nd);
        if(nd->type == "DC" || nd->type == "CMDS") v.push_back(nd);
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
    if(s == "DC") getDeclarations(v, node);
    else if(s == "CMDS") {
        getCmds(v, node);
    }
    else if(s == "METODO") {
        getMethod(node, v);
    }
}

void compressStructure(ast::Node* & node) {
    if(node->tokens.empty()) return;
    std::deque<ast::Node*> v;
    compressSubTree(node->type, node, v);
    node->tokens = v;
}

void eraseEmptyProductions(ast::Node* & node) {
    for(int i = 0; i < size(node->tokens); i++) {
        ast::Node* n = node->tokens[i];
        if(n->type == "Punctuation") {
            node->tokens.erase(node->tokens.begin() + i);
            i--;
            continue;
        }
        if(n->tokens.empty()) continue;
        if(n->tokens[0]->type == "VAZIO") {
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
        if((*itInit)->type != "Keyword") break;
        init->tokens.erase(itInit);
        itInit++;
    }

    init->value = "public static void main";
}

void compressTest(ast::Node* & node) {
    for(auto & n : node->tokens) {
        if(n->tokens.empty()) continue;
        else {
            if(n->type == "DC") {
                compressStructure(n);
            } else if(n->type == "CMDS") {
                compressStructure(n);
                filterCmds(n);
            }
            else if(n->type == "METODO") {
                compressStructure(n);
            }
            compressTest(n);
        }
    }
}

ast::Node* compress(ast::Node* & root) {
    eraseEmptyProductions(root);

    // retirar entradas do programa
    root->tokens.pop_front();
    root->tokens.pop_front();

    removeInit(root);
    compressTest(root);
    return root;
}

ast::Node* compress(ast::Node* node, ast::Node* compressed, std::deque<ast::Node*> pilha) {
    return new ast::Node("compress", "compress", true);
}

ast::Node* buildAST(std::vector<lex::token>::iterator & token) {
    ast::Node* parseTree = ast::buildParseTree(token);
    return compress(parseTree);
}

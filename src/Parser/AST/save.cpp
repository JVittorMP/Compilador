#include "../../basic.h"
#include "ast.h"


void explore(ast::Node** node, int i = 0) {
    std::cout << std::endl << (((*node)->value.empty()) ? "@" : tab(i) + std::to_string(i) + " " + (*node)->value) << " ";
    for(int j = 0; j < size((*node)->tokens); j++) {
        auto n = (*node)->tokens[j];
        if((*n).tokens.empty()) std::cout << (((*n).value.empty()) ? "@" : (*n).value) << " ";
        else {
            explore(&n, i + 1);
            //if(j != size((*node)->tokens) - 1) std::cout << std::endl << tab(i) + std::to_string(i) + " ";
        }
    }
}

void explore02(ast::Node** node, int i = 0) {
    for(int j = 0; j < size((*node)->tokens); j++) {
        auto n = (*node)->tokens[j];
        std::cout << std::endl << tab(i) << "[(" << std::to_string(i) << ":" << std::to_string(j) << "):" << (*n).type << ", " << (*n).value << "]";
        explore02(&n, i + 1);
    }
}

void getVars(std::deque<ast::Node*> & v, ast::Node** cur) {
    if((*cur)->tokens.empty()) return;
    for(auto n : (*cur)->tokens) {
        if((*n).type == "Identifier") v.push_back(n);
        getVars(v, &n);
    }
}

void getDeclarations(std::deque<ast::Node*> & dc, ast::Node** cur) {
    if((*cur)->tokens.empty()) return;
    for(auto n : (*cur)->tokens) {
        if((*n).type == "VAR") {
            for(auto b : (*n).tokens) {
                if(b->type == "VARS") {
                    std::deque<ast::Node*> vars;
                    getVars(vars, &b);
                    b->tokens = vars;
                }
            }
            dc.push_back(n);
        } else {
            getDeclarations(dc, &n);
        }

    }
}

std::deque<ast::Node*> getTermo(std::deque<ast::Node*> v, ast::Node** cur) {
    if((*cur)->tokens[0]->type == "OP_UN") {
        (*cur)->tokens[1]->tokens[0]->value.insert((*cur)->tokens[1]->tokens[0]->value.begin(), '-');
        (*cur)->tokens.pop_front();
    }
    std::cout << "termo: " << &(*(*cur)) << std::endl;
    *cur = (*cur)->tokens[0]->tokens[0];
    return v;
}

std::deque<ast::Node*> getExpression(std::deque<ast::Node*> v, ast::Node** cur) {
    for(auto nd : (*cur)->tokens) {
        if(nd->type == "TERMO") {
            std::cout << "expression: " << &(*(*cur)) << std::endl;
            getTermo(v, &nd);
        }
        std::cout << std::endl;
    }
    return v;
}

void getCmds(std::deque<ast::Node*> & cmds, ast::Node** cur) {
    if((*cur)->tokens.empty()) return;
    for(auto n : (*cur)->tokens) {
        if((*n).type == "CMD" || (*n).type == "CONDITIONAL_CMD") {
            if((*n).tokens[0]->value == "System.out.println") {
                std::deque<ast::Node*> subs;
                for(auto nd : (*n).tokens) {
                    if(!nd->terminal || nd->value == "System.out.println") subs.push_back(nd);
                }
                (*n).tokens = subs;
            }
            cmds.push_back(n);
        } else {
            getCmds(cmds, &n);
        }

    }
}

void orderOutput(ast::Node** node) {

}



void orderAtribution(ast::Node** node) {
    std::deque<ast::Node*> v;
    ast::Node** id = &(*node)->tokens[0];
    ast::Node** ri = &(*node)->tokens[1];
    ast::Node** op = &(*ri)->tokens[0];
    ast::Node** ex = &(*ri)->tokens[1]->tokens[0];
    auto* novo = new ast::Node({(*op)->type, (*op)->value, (*op)->terminal});
    novo->tokens.push_back((*id));
    novo->tokens.push_back((*ex));
    getExpression(v, ex);
    //ex->tokens = v;
    //node = novo;
}

void filterCmds(ast::Node** node) {
    for(auto n : (*node)->tokens) {
        std::string s = (*n).tokens.front()->type;
        if(s == "Keyword") orderOutput(&n);
        else if(s == "Identifier") orderAtribution(&n);
    }
}

void getParams(std::deque<ast::Node*> & v, ast::Node** cur) {
    if((*cur)->tokens.empty()) return;
    for(auto n : (*cur)->tokens) {
        if((*n).type == "PARAMS") {
            v.insert(v.end(), (*n).tokens.begin(), (*n).tokens.end());
            break;
        }
        getVars(v, &n);
    }
}

void compressSubTree(const std::string & s, ast::Node** node, std::deque<ast::Node*> & v) {
    if(s == "DC") getDeclarations(v, node);
    else if(s == "CMDS") {
        getCmds(v, node);
    }
    else if(s == "PARAMS") getParams(v, node);
}

void compressStructure(ast::Node** node) {
    if((*node)->tokens.empty()) return;
    std::deque<ast::Node*> v;
    compressSubTree((*node)->type, node, v);
    (*node)->tokens = v;
}

void eraseEmptyProductions(ast::Node** node) {
    for(int i = 0; i < size((*node)->tokens); i++) {
        ast::Node** n = &(*node)->tokens[i];
        if((*n)->tokens.empty()) continue;
        if((*n)->tokens[0]->value == "VAZIO") {
            (*node)->tokens.erase((*node)->tokens.begin() + i);
            i--;
            continue;
        }
        eraseEmptyProductions(n);
    }
}

void compressTest(ast::Node** node) {
    eraseEmptyProductions(node);
    for(auto n : (*node)->tokens) {
        if((*n).tokens.empty()) continue;
        else {
            if((*n).type == "DC") {
                compressStructure(&n);
            } else if((*n).type == "CMDS") {
                compressStructure(&n);
                filterCmds(&n);
            } /*else if((*n)->type == "PARAMS") {
                compressDecl(n);
            }*/
            compressTest(&n);
        }
    }
}

void compress(ast::Node** root) {
    eraseEmptyProductions(root);
    compressTest(root);
}

ast::Node** compress(ast::Node** node, ast::Node** compressed, std::deque<ast::Node*> pilha) {
    ast::Node* cur = new ast::Node("compress", "compress", true);
    ast::Node** n = &cur;
    return n;
}
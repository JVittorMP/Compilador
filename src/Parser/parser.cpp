#include "sin.h"
#include "AST/ast.h"

std::string tab(int i) {
    return std::string(i * 3, ' ');
}

void exploreTNode(ast::Node* node, int i = 0) {
    for(int j = 0; j < size(node->tokens); j++) {
        auto n = node->tokens[j];
        std::cout << std::endl << tab(i) << "[(" << std::to_string(i) << ":" << std::to_string(j) << "):" << n->type.asString() << ", " << n->value << "]";
        exploreTNode(n, i + 1);
    }
}

void exploreNode(ast::Node* node, int i = 0) {
    std::cout << std::endl << tab(i) << "[(0:0):" << node->type.asString() << ", " << node->value << "]";
    exploreTNode(node, i + 1);
}

int PROG(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int INIT(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int METODO(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int PARAMS(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int MAIS_PARAMS(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int DC(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int MAIS_DC(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int VAR(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int VARS(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int MAIS_VAR(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int TIPO(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int CMDS(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int CONDITIONAL_CMD(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int CMD(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int PFALSA(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int RESTO_IDENT(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int LISTA_ARG(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int ARGUMENTOS(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int MAIS_IDENT(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int EXP_IDENT(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int CONDICAO(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int RELACAO(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int EXPRESSAO(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int TERMO(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int OP_UN(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int FATOR(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int OUTROS_TERMOS(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int OP_AD(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int MAIS_FATORES(ast::Node* node, std::deque<lex::token>::iterator & tokens);
int OP_MUL(ast::Node* node, std::deque<lex::token>::iterator & tokens);

ast::Node* parse(ast::Node* node, std::deque<lex::token>::iterator & tokens);

int findNonTerminal(enum lex::Type::pattern p, ast::Node* node, std::deque<lex::token>::iterator & token) {
    switch (p) {
        case lex::Type::pattern::PROG :
            if(PROG(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::INIT :
            if(INIT(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::METODO:
            if(METODO(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::PARAMS:
            if(PARAMS(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::MAIS_PARAMS:
            if(MAIS_PARAMS(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::DC:
            if(DC(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::MAIS_DC:
            if(MAIS_DC(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::VAR:
            if(VAR(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::VARS:
            if(VARS(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::MAIS_VAR:
            if(MAIS_VAR(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::TIPO:
            if(TIPO(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::CMDS:
            if(CMDS(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::CONDITIONAL_CMD:
            if(CONDITIONAL_CMD(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::CMD:
            if(CMD(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::PFALSA:
            if(PFALSA(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::RESTO_IDENT:
            if(RESTO_IDENT(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::LISTA_ARG:
            if(LISTA_ARG(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::ARGUMENTOS:
            if(ARGUMENTOS(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::MAIS_IDENT:
            if(MAIS_IDENT(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::EXP_IDENT:
            if(EXP_IDENT(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::CONDICAO:
            if(CONDICAO(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::RELACAO:
            if(RELACAO(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::EXPRESSAO:
            if(EXPRESSAO(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::TERMO:
            if(TERMO(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::OP_UN:
            if(OP_UN(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::FATOR:
            if(FATOR(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::OUTROS_TERMOS:
            if(OUTROS_TERMOS(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::OP_AD:
            if(OP_AD(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::MAIS_FATORES:
            if(MAIS_FATORES(node, token)) return SUCCESS;
            return FAIL;
        case lex::Type::pattern::OP_MUL:
            if(OP_MUL(node, token)) return SUCCESS;
            return FAIL;
        default:
            return FAIL;
    }
}

int isProductionValid(ast::Node* node, std::deque<lex::token>::iterator & token, std::deque<lex::token> & lexemas) {
    for(auto & lexema : lexemas) {
        if((*token).value == "$") return FAIL;
        if(lexema.type.status()) {
            if(lexema.type.pattern == lex::Type::pattern::IDENTIFIER && (*token).type.pattern == lex::Type::pattern::IDENTIFIER) {
                // std::cout << lex::Type::pattern::IDENTIFIER << std::endl;
            } else if(lexema.value != (*token).value) return FAIL;
            node->tokens.push_back(ast::Node::pointer((*token)));
            token++;
        } else {
            auto* novo = ast::Node::pointer(lexema.type, lexema.value);
            node->tokens.push_back(novo);
            if(!findNonTerminal(lexema.type.pattern, novo, token)) return FAIL;
        }
    }
    return SUCCESS;
}

// Validar para lançar exceção, de modo a interromper o fluxo do programa
ast::Node* parse(std::deque<lex::token>::iterator & token) {
    auto* root = ast::Node::pointer(lex::Type(lex::Type::pattern::PROG));
    bool ans = PROG(root, token);
    if(ans) {
        std::cout << "Parser: Tudo Certo!" <<  std::endl << std::endl;
    } else {
        std::cout << "Parser: Tudo Errado! Fim dos Tempos!" <<  std::endl;
    }
    return root;
}

int PROG(ast::Node* node, std::deque<lex::token>::iterator & token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::PUBLIC));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::CLASS));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::IDENTIFIER));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::LCHAVE));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::INIT));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::METODO));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::RCHAVE));
    if(isProductionValid(node, token, lexemas)) return SUCCESS;
    return FAIL;
}

int INIT(ast::Node* node, std::deque<lex::token>::iterator & token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::PUBLIC));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::STATIC));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::VOID));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::MAIN));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::LPARENTESE));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::RPARENTESE));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::LCHAVE));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::DC));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::CMDS));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::RCHAVE));
    if(isProductionValid(node, token, lexemas)) return SUCCESS;
    return FAIL;
}

int METODO(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::PUBLIC));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::STATIC));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::TIPO));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::IDENTIFIER));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::LPARENTESE));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::PARAMS));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::RPARENTESE));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::LCHAVE));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::DC));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::CMDS));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::RETURN));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::EXPRESSAO));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::PONTO_VIRGULA));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::RCHAVE));
    if((*token).value == lex::Type::asValue(lex::Type::pattern::PUBLIC)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::Type::pattern::VAZIO}));
    return SUCCESS;
}

int PARAMS(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::TIPO));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::IDENTIFIER));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::MAIS_PARAMS));
    if((*token).value == lex::Type::asValue(lex::Type::pattern::DOUBLE)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::Type::pattern::VAZIO}));
    return SUCCESS;
}

int MAIS_PARAMS(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::VIRGULA));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::PARAMS));
    if((*token).value == lex::Type::asValue(lex::Type::pattern::VIRGULA)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::Type::pattern::VAZIO}));
    return SUCCESS;
}

int DC(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::VAR));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::MAIS_DC));
    if((*token).value == lex::Type::asValue(lex::Type::pattern::DOUBLE)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::Type::pattern::VAZIO}));
    return SUCCESS;
}

int MAIS_DC(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::PONTO_VIRGULA));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::DC));
    if((*token).value == lex::Type::asValue(lex::Type::pattern::PONTO_VIRGULA)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::Type::pattern::VAZIO}));
    return SUCCESS;
}

int VAR(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::TIPO));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::VARS));
    if(isProductionValid(node, token, lexemas)) return SUCCESS;
    return FAIL;
}

int VARS(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::IDENTIFIER));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::MAIS_VAR));
    if(isProductionValid(node, token, lexemas)) return SUCCESS;
    return FAIL;
}

int MAIS_VAR(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::VIRGULA));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::VARS));
    if((*token).value == lex::Type::asValue(lex::Type::pattern::VIRGULA)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::Type::pattern::VAZIO}));
    return SUCCESS;
}

int TIPO(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::DOUBLE));
    if(isProductionValid(node, token, lexemas)) return SUCCESS;
    return FAIL;
}

int CMDS(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    if ((*token).type.pattern == lex::Type::pattern::IDENTIFIER || (*token).value == lex::Type::asValue(lex::Type::pattern::OUTPUT)) {
        lexemas.emplace_back(lex::Type(lex::Type::pattern::CMD));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::PONTO_VIRGULA));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::CMDS));
    } else if((*token).value == lex::Type::asValue(lex::Type::pattern::IF) || (*token).value == lex::Type::asValue(lex::Type::pattern::WHILE)) {
        lexemas.emplace_back(lex::Type(lex::Type::pattern::CONDITIONAL_CMD));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::CMDS));
    } else {
        node->tokens.push_back(ast::Node::pointer(lex::Type{lex::Type::pattern::VAZIO}));
        return SUCCESS;
    }
    if(isProductionValid(node, token, lexemas)) return SUCCESS;
    return FAIL;
}

int CONDITIONAL_CMD(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    if((*token).value == lex::Type::asValue(lex::Type::pattern::IF)) {
        lexemas.emplace_back(lex::Type(lex::Type::pattern::IF));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::LPARENTESE));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::CONDICAO));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::RPARENTESE));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::LCHAVE));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::CMDS));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::RCHAVE));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::PFALSA));
    } else if((*token).value == lex::Type::asValue(lex::Type::pattern::WHILE)) {
        lexemas.emplace_back(lex::Type(lex::Type::pattern::WHILE));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::LPARENTESE));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::CONDICAO));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::RPARENTESE));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::LCHAVE));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::CMDS));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::RCHAVE));
    } else {
        return FAIL;
    }
    if(isProductionValid(node, token, lexemas)) return SUCCESS;
    return FAIL;
}

int CMD(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    if((*token).value == lex::Type::asValue(lex::Type::pattern::OUTPUT)) {
        lexemas.emplace_back(lex::Type(lex::Type::pattern::OUTPUT));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::LPARENTESE));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::EXPRESSAO));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::RPARENTESE));
    } else if((*token).type.pattern == lex::Type::pattern::IDENTIFIER) {
        lexemas.emplace_back(lex::Type(lex::Type::pattern::IDENTIFIER));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::RESTO_IDENT));
    } else {
        return FAIL;
    }
    if(isProductionValid(node, token, lexemas)) return SUCCESS;
    return FAIL;
}

int PFALSA(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::ELSE));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::LCHAVE));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::CMDS));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::RCHAVE));
    if((*token).value == lex::Type::asValue(lex::Type::pattern::ELSE)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::Type::pattern::VAZIO}));
    return SUCCESS;
}


int RESTO_IDENT(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    if((*token).value == lex::Type::asValue(lex::Type::pattern::ATRIBUICAO)) {
        lexemas.emplace_back(lex::Type(lex::Type::pattern::ATRIBUICAO));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::EXP_IDENT));
    } else if((*token).value == lex::Type::asValue(lex::Type::pattern::LPARENTESE)) {
        lexemas.emplace_back(lex::Type(lex::Type::pattern::LPARENTESE));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::LISTA_ARG));
        lexemas.emplace_back(lex::Type(lex::Type::pattern::RPARENTESE));
    } else {
        return FAIL;
    }
    if(isProductionValid(node, token, lexemas)) return SUCCESS;
    return FAIL;
}

int LISTA_ARG(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::ARGUMENTOS));
    if((*token).type.pattern == lex::Type::pattern::IDENTIFIER) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::Type::pattern::VAZIO}));
    return SUCCESS;
}

int ARGUMENTOS(ast::Node* node, std::deque<lex::token>::iterator & token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::IDENTIFIER));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::MAIS_IDENT));
    if((*token).type == lex::Type(lex::Type::pattern::IDENTIFIER)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
    }
    return FAIL;
}

int MAIS_IDENT(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::VIRGULA));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::ARGUMENTOS));
    if((*token).value == lex::Type::asValue(lex::Type::pattern::VIRGULA)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::Type::pattern::VAZIO}));
    return SUCCESS;
}

int EXP_IDENT(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::EXPRESSAO));
    if( (*token).type == lex::Type(lex::Type::pattern::IDENTIFIER) ||
        (*token).type == lex::Type(lex::Type::pattern::NUM) ||
        (*token).value == lex::Type::asValue(lex::Type::pattern::LPARENTESE) ||
        (*token).value == lex::Type::asValue(lex::Type::pattern::SUBTRACAO)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    } else if((*token).value == lex::Type::asValue(lex::Type::pattern::INPUT)) {
        node->tokens.push_back(ast::Node::pointer((*token)));
        node->tokens.push_back(ast::Node::pointer((*token)));
        token++;
        return SUCCESS;
    }
    return FAIL;
}

int CONDICAO(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::EXPRESSAO));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::RELACAO));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::EXPRESSAO));
    if ((*token).type == lex::Type(lex::Type::pattern::IDENTIFIER) ||
        (*token).type == lex::Type(lex::Type::pattern::NUM) ||
        (*token).value == lex::Type::asValue(lex::Type::pattern::LPARENTESE) ||
        (*token).value == lex::Type::asValue(lex::Type::pattern::SUBTRACAO)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return FAIL;
}

bool isOperator(std::string s) {
    return s == "<=" || s == ">=" || s == "==" || s == "!=" || s == "<" || s== ">";
}


int RELACAO(ast::Node* node, std::deque<lex::token>::iterator &token) {
    if(isOperator((*token).value) /*(*token).type == lex::Type(lex::Type::pattern::OPERATOR)*/) {
        node->tokens.push_back(ast::Node::pointer((*token)));
        token++;
        return SUCCESS;
    }
    return FAIL;
}

int EXPRESSAO(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::TERMO));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::OUTROS_TERMOS));
    if ((*token).type == lex::Type(lex::Type::pattern::IDENTIFIER) ||
        (*token).type == lex::Type(lex::Type::pattern::NUM) ||
        (*token).value == lex::Type::asValue(lex::Type::pattern::LPARENTESE) ||
        (*token).value == lex::Type::asValue(lex::Type::pattern::SUBTRACAO)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return FAIL;
}

int TERMO(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::OP_UN));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::FATOR));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::MAIS_FATORES));
    if( (*token).type == lex::Type(lex::Type::pattern::IDENTIFIER) ||
        (*token).type == lex::Type(lex::Type::pattern::NUM) ||
        (*token).value == lex::Type::asValue(lex::Type::pattern::LPARENTESE) ||
        (*token).value == lex::Type::asValue(lex::Type::pattern::SUBTRACAO)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return FAIL;
}

int OP_UN(ast::Node* node, std::deque<lex::token>::iterator &token) {
    if((*token).value == lex::Type::asValue(lex::Type::pattern::SUBTRACAO)) {
        node->tokens.push_back(ast::Node::pointer((*token)));
        token++;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::Type::pattern::VAZIO}));
    return SUCCESS;
}

int FATOR(ast::Node* node, std::deque<lex::token>::iterator &token) {
    if((*token).type == lex::Type(lex::Type::pattern::IDENTIFIER) || (*token).type == lex::Type(lex::Type::pattern::NUM)) {
        node->tokens.push_back(ast::Node::pointer((*token)));
        token++;
        return SUCCESS;
    }
    return FAIL;
}

int OUTROS_TERMOS(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::OP_AD));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::TERMO));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::OUTROS_TERMOS));
    if((*token).value == lex::Type::asValue(lex::Type::pattern::ADICAO) || (*token).value == lex::Type::asValue(lex::Type::pattern::SUBTRACAO)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::Type::pattern::VAZIO}));
    return SUCCESS;
}

int OP_AD(ast::Node* node, std::deque<lex::token>::iterator &token) {
    if((*token).value == lex::Type::asValue(lex::Type::pattern::ADICAO) || (*token).value == lex::Type::asValue(lex::Type::pattern::SUBTRACAO)) {
        node->tokens.push_back(ast::Node::pointer((*token)));
        token++;
        return SUCCESS;
    }
    return FAIL;
}

int MAIS_FATORES(ast::Node* node, std::deque<lex::token>::iterator &token) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::Type::pattern::OP_MUL));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::FATOR));
    lexemas.emplace_back(lex::Type(lex::Type::pattern::MAIS_FATORES));
    if((*token).value == lex::Type::asValue(lex::Type::pattern::MULTIPLICACAO) || (*token).value == lex::Type::asValue(lex::Type::pattern::DIVISAO)) {
        if(isProductionValid(node, token, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::Type::pattern::VAZIO}));
    return SUCCESS;
}

int OP_MUL(ast::Node* node, std::deque<lex::token>::iterator &token) {
    if((*token).value == lex::Type::asValue(lex::Type::pattern::MULTIPLICACAO) || (*token).value == lex::Type::asValue(lex::Type::pattern::DIVISAO)) {
        node->tokens.push_back(ast::Node::pointer((*token)));
        token++;
        return SUCCESS;
    }
    return FAIL;
}
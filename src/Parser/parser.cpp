#include "../def.h"

/**
 * @def
 * Direciona o fluxo de execução ao bloco que trata o elemento não terminal corrente.
 */
int sin::findNonTerminal(const enum lex::pattern p, ast::Node* node, sin::cursor & cursor) {
    switch (p) {
        case lex::pattern::PROG :
            if(PROG(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::INIT :
            if(INIT(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::METODO:
            if(METODO(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::PARAMS:
            if(PARAMS(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::MAIS_PARAMS:
            if(MAIS_PARAMS(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::DC:
            if(DC(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::MAIS_DC:
            if(MAIS_DC(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::VAR:
            if(VAR(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::VARS:
            if(VARS(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::MAIS_VAR:
            if(MAIS_VAR(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::TIPO:
            if(TIPO(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::CMDS:
            if(CMDS(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::CONDITIONAL_CMD:
            if(CONDITIONAL_CMD(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::CMD:
            if(CMD(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::PFALSA:
            if(PFALSA(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::RESTO_IDENT:
            if(RESTO_IDENT(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::LISTA_ARG:
            if(LISTA_ARG(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::ARGUMENTOS:
            if(ARGUMENTOS(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::MAIS_IDENT:
            if(MAIS_IDENT(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::EXP_IDENT:
            if(EXP_IDENT(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::CONDICAO:
            if(CONDICAO(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::RELACAO:
            if(RELACAO(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::EXPRESSAO:
            if(EXPRESSAO(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::TERMO:
            if(TERMO(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::OP_UN:
            if(OP_UN(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::FATOR:
            if(FATOR(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::OUTROS_TERMOS:
            if(OUTROS_TERMOS(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::OP_AD:
            if(OP_AD(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::MAIS_FATORES:
            if(MAIS_FATORES(node, cursor)) return SUCCESS;
            return FAIL;
        case lex::pattern::OP_MUL:
            if(OP_MUL(node, cursor)) return SUCCESS;
            return FAIL;
        default:
            return FAIL;
    }
}

/**
 *
 * @def
 * Avalia se a produção atual é válida
 * <br> Produção Terminal: Tenta realizar um match entre os tokens
 * <br> Produção Não Terminal: Continua a busca por um elemento terminal
 */
int sin::isProductionValid(ast::Node* node, sin::cursor & cursor, std::deque<lex::token> & lexemas) {
    for(auto & lexema : lexemas) {
        if(cursor.token().value == "$") return FAIL;
        if(lexema.type.status()) {
            if(lexema.type.pattern == lex::pattern::IDENTIFIER && cursor.token().type.pattern == lex::pattern::IDENTIFIER) {
                // std::cout << lex::pattern::IDENTIFIER << std::endl;
            } else if(lexema.value != cursor.token().value) return FAIL;
            node->tokens.push_back(ast::Node::pointer(cursor.token()));
            cursor.next();
        } else {
            auto novo = ast::Node::pointer(lexema.type, lexema.value);
            node->tokens.push_back(novo);
            if(!findNonTerminal(lexema.type.pattern, novo, cursor)) return FAIL;
        }
    }
    return SUCCESS;
}

int sin::PROG(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::PUBLIC));
    lexemas.emplace_back(lex::Type(lex::pattern::CLASS));
    lexemas.emplace_back(lex::Type(lex::pattern::IDENTIFIER));
    lexemas.emplace_back(lex::Type(lex::pattern::LCHAVE));
    lexemas.emplace_back(lex::Type(lex::pattern::INIT));
    lexemas.emplace_back(lex::Type(lex::pattern::METODO));
    lexemas.emplace_back(lex::Type(lex::pattern::RCHAVE));
    if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::INIT(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::PUBLIC));
    lexemas.emplace_back(lex::Type(lex::pattern::STATIC));
    lexemas.emplace_back(lex::Type(lex::pattern::VOID));
    lexemas.emplace_back(lex::Type(lex::pattern::MAIN));
    lexemas.emplace_back(lex::Type(lex::pattern::LPARENTESE));
    lexemas.emplace_back(lex::Type(lex::pattern::RPARENTESE));
    lexemas.emplace_back(lex::Type(lex::pattern::LCHAVE));
    lexemas.emplace_back(lex::Type(lex::pattern::DC));
    lexemas.emplace_back(lex::Type(lex::pattern::CMDS));
    lexemas.emplace_back(lex::Type(lex::pattern::RCHAVE));
    if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::METODO(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::PUBLIC));
    lexemas.emplace_back(lex::Type(lex::pattern::STATIC));
    lexemas.emplace_back(lex::Type(lex::pattern::TIPO));
    lexemas.emplace_back(lex::Type(lex::pattern::IDENTIFIER));
    lexemas.emplace_back(lex::Type(lex::pattern::LPARENTESE));
    lexemas.emplace_back(lex::Type(lex::pattern::PARAMS));
    lexemas.emplace_back(lex::Type(lex::pattern::RPARENTESE));
    lexemas.emplace_back(lex::Type(lex::pattern::LCHAVE));
    lexemas.emplace_back(lex::Type(lex::pattern::DC));
    lexemas.emplace_back(lex::Type(lex::pattern::CMDS));
    lexemas.emplace_back(lex::Type(lex::pattern::RETURN));
    lexemas.emplace_back(lex::Type(lex::pattern::EXPRESSAO));
    lexemas.emplace_back(lex::Type(lex::pattern::PONTO_VIRGULA));
    lexemas.emplace_back(lex::Type(lex::pattern::RCHAVE));
    if(cursor.token().value == lex::Type::asValue(lex::pattern::PUBLIC)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::pattern::VAZIO}));
    return SUCCESS;
}

int sin::PARAMS(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::TIPO));
    lexemas.emplace_back(lex::Type(lex::pattern::IDENTIFIER));
    lexemas.emplace_back(lex::Type(lex::pattern::MAIS_PARAMS));
    if(cursor.token().value == lex::Type::asValue(lex::pattern::DOUBLE)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::pattern::VAZIO}));
    return SUCCESS;
}

int sin::MAIS_PARAMS(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::VIRGULA));
    lexemas.emplace_back(lex::Type(lex::pattern::PARAMS));
    if(cursor.token().value == lex::Type::asValue(lex::pattern::VIRGULA)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::pattern::VAZIO}));
    return SUCCESS;
}

int sin::DC(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::VAR));
    lexemas.emplace_back(lex::Type(lex::pattern::MAIS_DC));
    if(cursor.token().value == lex::Type::asValue(lex::pattern::DOUBLE)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::pattern::VAZIO}));
    return SUCCESS;
}

int sin::MAIS_DC(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::PONTO_VIRGULA));
    lexemas.emplace_back(lex::Type(lex::pattern::DC));
    if(cursor.token().value == lex::Type::asValue(lex::pattern::PONTO_VIRGULA)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::pattern::VAZIO}));
    return SUCCESS;
}

int sin::VAR(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::TIPO));
    lexemas.emplace_back(lex::Type(lex::pattern::VARS));
    if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::VARS(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::IDENTIFIER));
    lexemas.emplace_back(lex::Type(lex::pattern::MAIS_VAR));
    if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::MAIS_VAR(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::VIRGULA));
    lexemas.emplace_back(lex::Type(lex::pattern::VARS));
    if(cursor.token().value == lex::Type::asValue(lex::pattern::VIRGULA)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::pattern::VAZIO}));
    return SUCCESS;
}

int sin::TIPO(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::DOUBLE));
    if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::CMDS(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    if (cursor.token().type.pattern == lex::pattern::IDENTIFIER || cursor.token().value == lex::Type::asValue(lex::pattern::OUTPUT)) {
        lexemas.emplace_back(lex::Type(lex::pattern::CMD));
        lexemas.emplace_back(lex::Type(lex::pattern::PONTO_VIRGULA));
        lexemas.emplace_back(lex::Type(lex::pattern::CMDS));
    } else if(cursor.token().value == lex::Type::asValue(lex::pattern::IF) || cursor.token().value == lex::Type::asValue(lex::pattern::WHILE)) {
        lexemas.emplace_back(lex::Type(lex::pattern::CONDITIONAL_CMD));
        lexemas.emplace_back(lex::Type(lex::pattern::CMDS));
    } else {
        node->tokens.push_back(ast::Node::pointer(lex::Type{lex::pattern::VAZIO}));
        return SUCCESS;
    }
    if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::CONDITIONAL_CMD(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    if(cursor.token().value == lex::Type::asValue(lex::pattern::IF)) {
        lexemas.emplace_back(lex::Type(lex::pattern::IF));
        lexemas.emplace_back(lex::Type(lex::pattern::LPARENTESE));
        lexemas.emplace_back(lex::Type(lex::pattern::CONDICAO));
        lexemas.emplace_back(lex::Type(lex::pattern::RPARENTESE));
        lexemas.emplace_back(lex::Type(lex::pattern::LCHAVE));
        lexemas.emplace_back(lex::Type(lex::pattern::CMDS));
        lexemas.emplace_back(lex::Type(lex::pattern::RCHAVE));
        lexemas.emplace_back(lex::Type(lex::pattern::PFALSA));
    } else if(cursor.token().value == lex::Type::asValue(lex::pattern::WHILE)) {
        lexemas.emplace_back(lex::Type(lex::pattern::WHILE));
        lexemas.emplace_back(lex::Type(lex::pattern::LPARENTESE));
        lexemas.emplace_back(lex::Type(lex::pattern::CONDICAO));
        lexemas.emplace_back(lex::Type(lex::pattern::RPARENTESE));
        lexemas.emplace_back(lex::Type(lex::pattern::LCHAVE));
        lexemas.emplace_back(lex::Type(lex::pattern::CMDS));
        lexemas.emplace_back(lex::Type(lex::pattern::RCHAVE));
    } else {
        return FAIL;
    }
    if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::CMD(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    if(cursor.token().value == lex::Type::asValue(lex::pattern::OUTPUT)) {
        lexemas.emplace_back(lex::Type(lex::pattern::OUTPUT));
        lexemas.emplace_back(lex::Type(lex::pattern::LPARENTESE));
        lexemas.emplace_back(lex::Type(lex::pattern::EXPRESSAO));
        lexemas.emplace_back(lex::Type(lex::pattern::RPARENTESE));
    } else if(cursor.token().type.pattern == lex::pattern::IDENTIFIER) {
        lexemas.emplace_back(lex::Type(lex::pattern::IDENTIFIER));
        lexemas.emplace_back(lex::Type(lex::pattern::RESTO_IDENT));
    } else {
        return FAIL;
    }
    if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::PFALSA(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::ELSE));
    lexemas.emplace_back(lex::Type(lex::pattern::LCHAVE));
    lexemas.emplace_back(lex::Type(lex::pattern::CMDS));
    lexemas.emplace_back(lex::Type(lex::pattern::RCHAVE));
    if(cursor.token().value == lex::Type::asValue(lex::pattern::ELSE)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::pattern::VAZIO}));
    return SUCCESS;
}


int sin::RESTO_IDENT(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    if(cursor.token().value == lex::Type::asValue(lex::pattern::ATRIBUICAO)) {
        lexemas.emplace_back(lex::Type(lex::pattern::ATRIBUICAO));
        lexemas.emplace_back(lex::Type(lex::pattern::EXP_IDENT));
    } else if(cursor.token().value == lex::Type::asValue(lex::pattern::LPARENTESE)) {
        lexemas.emplace_back(lex::Type(lex::pattern::LPARENTESE));
        lexemas.emplace_back(lex::Type(lex::pattern::LISTA_ARG));
        lexemas.emplace_back(lex::Type(lex::pattern::RPARENTESE));
    } else {
        return FAIL;
    }
    if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::LISTA_ARG(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::ARGUMENTOS));
    if(cursor.token().type.pattern == lex::pattern::IDENTIFIER) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::pattern::VAZIO}));
    return SUCCESS;
}

int sin::ARGUMENTOS(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::IDENTIFIER));
    lexemas.emplace_back(lex::Type(lex::pattern::MAIS_IDENT));
    if(cursor.token().type == lex::Type(lex::pattern::IDENTIFIER)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
    }
    return FAIL;
}

int sin::MAIS_IDENT(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::VIRGULA));
    lexemas.emplace_back(lex::Type(lex::pattern::ARGUMENTOS));
    if(cursor.token().value == lex::Type::asValue(lex::pattern::VIRGULA)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::pattern::VAZIO}));
    return SUCCESS;
}

int sin::EXP_IDENT(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::EXPRESSAO));
    if( cursor.token().type == lex::Type(lex::pattern::IDENTIFIER) ||
        cursor.token().type == lex::Type(lex::pattern::NUM) ||
        cursor.token().value == lex::Type::asValue(lex::pattern::LPARENTESE) ||
        cursor.token().value == lex::Type::asValue(lex::pattern::SUBTRACAO)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    if(cursor.token().value == lex::Type::asValue(lex::pattern::INPUT)) {
        node->tokens.push_back(ast::Node::pointer(cursor.token()));
        node->tokens.push_back(ast::Node::pointer(cursor.token()));
        cursor.next();
        return SUCCESS;
    }
    return FAIL;
}

int sin::CONDICAO(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::EXPRESSAO));
    lexemas.emplace_back(lex::Type(lex::pattern::RELACAO));
    lexemas.emplace_back(lex::Type(lex::pattern::EXPRESSAO));
    if (cursor.token().type == lex::Type(lex::pattern::IDENTIFIER) ||
        cursor.token().type == lex::Type(lex::pattern::NUM) ||
        cursor.token().value == lex::Type::asValue(lex::pattern::LPARENTESE) ||
        cursor.token().value == lex::Type::asValue(lex::pattern::SUBTRACAO)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    return FAIL;
}

int sin::RELACAO(ast::Node* node, cursor & cursor) {
    if(/*isOperator(cursor.token().value)*/ cursor.token().type == lex::Type(lex::pattern::OPERATOR)) {
        node->tokens.push_back(ast::Node::pointer(cursor.token()));
        cursor.next();
        return SUCCESS;
    }
    return FAIL;
}

int sin::EXPRESSAO(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::TERMO));
    lexemas.emplace_back(lex::Type(lex::pattern::OUTROS_TERMOS));
    if (cursor.token().type == lex::Type(lex::pattern::IDENTIFIER) ||
        cursor.token().type == lex::Type(lex::pattern::NUM) ||
        cursor.token().value == lex::Type::asValue(lex::pattern::LPARENTESE) ||
        cursor.token().value == lex::Type::asValue(lex::pattern::SUBTRACAO)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    return FAIL;
}

int sin::TERMO(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::OP_UN));
    lexemas.emplace_back(lex::Type(lex::pattern::FATOR));
    lexemas.emplace_back(lex::Type(lex::pattern::MAIS_FATORES));
    if( cursor.token().type == lex::Type(lex::pattern::IDENTIFIER) ||
        cursor.token().type == lex::Type(lex::pattern::NUM) ||
        cursor.token().value == lex::Type::asValue(lex::pattern::LPARENTESE) ||
        cursor.token().value == lex::Type::asValue(lex::pattern::SUBTRACAO)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    return FAIL;
}

int sin::OP_UN(ast::Node* node, cursor & cursor) {
    if(cursor.token().value == lex::Type::asValue(lex::pattern::SUBTRACAO)) {
        node->tokens.push_back(ast::Node::pointer(cursor.token()));
        cursor.next();
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::pattern::VAZIO}));
    return SUCCESS;
}

int sin::FATOR(ast::Node* node, cursor & cursor) {
    if(cursor.token().type == lex::Type(lex::pattern::IDENTIFIER) || cursor.token().type == lex::Type(lex::pattern::NUM)) {
        node->tokens.push_back(ast::Node::pointer(cursor.token()));
        cursor.next();
        return SUCCESS;
    }
    return FAIL;
}

int sin::OUTROS_TERMOS(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::OP_AD));
    lexemas.emplace_back(lex::Type(lex::pattern::TERMO));
    lexemas.emplace_back(lex::Type(lex::pattern::OUTROS_TERMOS));
    if(cursor.token().value == lex::Type::asValue(lex::pattern::ADICAO) || cursor.token().value == lex::Type::asValue(lex::pattern::SUBTRACAO)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::pattern::VAZIO}));
    return SUCCESS;
}

int sin::OP_AD(ast::Node* node, cursor & cursor) {
    if(cursor.token().value == lex::Type::asValue(lex::pattern::ADICAO) || cursor.token().value == lex::Type::asValue(lex::pattern::SUBTRACAO)) {
        node->tokens.push_back(ast::Node::pointer(cursor.token()));
        cursor.next();
        return SUCCESS;
    }
    return FAIL;
}

int sin::MAIS_FATORES(ast::Node* node, cursor & cursor) {
    std::deque<lex::token> lexemas; 
    lexemas.emplace_back(lex::Type(lex::pattern::OP_MUL));
    lexemas.emplace_back(lex::Type(lex::pattern::FATOR));
    lexemas.emplace_back(lex::Type(lex::pattern::MAIS_FATORES));
    if(cursor.token().value == lex::Type::asValue(lex::pattern::MULTIPLICACAO) || cursor.token().value == lex::Type::asValue(lex::pattern::DIVISAO)) {
        if(isProductionValid(node, cursor, lexemas)) return SUCCESS;
        return FAIL;
    }
    node->tokens.push_back(ast::Node::pointer(lex::Type{lex::pattern::VAZIO}));
    return SUCCESS;
}

int sin::OP_MUL(ast::Node* node, cursor & cursor) {
    if(cursor.token().value == lex::Type::asValue(lex::pattern::MULTIPLICACAO) || cursor.token().value == lex::Type::asValue(lex::pattern::DIVISAO)) {
        node->tokens.push_back(ast::Node::pointer(cursor.token()));
        cursor.next();
        return SUCCESS;
    }
    return FAIL;
}

ast::Node* sin::parse(cursor & cursor) {
    auto root = ast::Node::pointer(lex::Type(lex::pattern::PROG));
    if(PROG(root, cursor)) {
        std::cout << "Syntatic Analisis Concluded!" <<  std::endl;
    } else {
        const auto token = cursor.previous();
        const std::string msg = std::format("On Line {}: After [{}] Declaration!", token.linha, token.value);
        throw compiler::Exception(compiler::Exception::type::SYNTACTIC, msg);
    }
    return root;
}

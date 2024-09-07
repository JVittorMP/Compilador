#include "ast.h"

void findNonTerminal(unsigned lexema_type, ast::Node* node, std::vector<lex::token>::iterator & token) {
    switch (lexema_type) {
        case lex::PROG :
            return ast::PROG(node, token);
        case lex::INIT :
            return ast::INIT(node, token);
        case lex::METODO:
            return ast::METODO(node, token);
        case lex::PARAMS:
            return ast::PARAMS(node, token);
        case lex::MAIS_PARAMS:
            return ast::MAIS_PARAMS(node, token);
        case lex::DC:
            return ast::DC(node, token);
        case lex::MAIS_DC:
            return ast::MAIS_DC(node, token);
        case lex::VAR:
            return ast::VAR(node, token);
        case lex::VARS:
            return ast::VARS(node, token);
        case lex::MAIS_VAR:
            return ast::MAIS_VAR(node, token);
        case lex::TIPO:
            return ast::TIPO(node, token);
        case lex::CMDS:
            return ast::CMDS(node, token);
        case lex::CONDITIONAL_CMD:
            return ast::CONDITIONAL_CMD(node, token);
        case lex::CMD:
            return ast::CMD(node, token);
        case lex::PFALSA:
            return ast::PFALSA(node, token);
        case lex::RESTO_IDENT:
            return ast::RESTO_IDENT(node, token);
        case lex::LISTA_ARG:
            return ast::LISTA_ARG(node, token);
        case lex::ARGUMENTOS:
            return ast::ARGUMENTOS(node, token);
        case lex::MAIS_IDENT:
            return ast::MAIS_IDENT(node, token);
        case lex::EXP_IDENT:
            return ast::EXP_IDENT(node, token);
        case lex::CONDICAO:
            return ast::CONDICAO(node, token);
        case lex::RELACAO:
            return ast::RELACAO(node, token);
        case lex::EXPRESSAO:
            return ast::EXPRESSAO(node, token);
        case lex::TERMO:
            return ast::TERMO(node, token);
        case lex::OP_UN:
            return ast::OP_UN(node, token);
        case lex::FATOR:
            return ast::FATOR(node, token);
        case lex::OUTROS_TERMOS:
            return ast::OUTROS_TERMOS(node, token);
        case lex::OP_AD:
            return ast::OP_AD(node, token);
        case lex::MAIS_FATORES:
            return ast::MAIS_FATORES(node, token);
        case lex::OP_MUL:
            return ast::OP_MUL(node, token);
        default:
            return;
    }
}

void isProductionValid(ast::Node* node, std::vector<lex::token>::iterator & token, std::vector<lex::lexema> & lexemas) {
    for(auto & lexema : lexemas) {
        if((*token).value == "$") return;
        if(lexema.terminal) {
            // node->tokens.back()->value += token->value;
            node->tokens.push_back(new ast::Node({token->type, token->value, lex::TERMINAL}));
            token++;
        } else {
            auto* novo = new ast::Node({lexema.value, lexema.value, lex::NON_TERMINAL});
            node->tokens.push_back(novo);
            findNonTerminal(lexema.type, novo, token);
        }
    }
}

ast::Node* ast::buildParseTree(std::vector<lex::token>::iterator & token) {
    auto* root = new Node({"PROG", "PROG", lex::NON_TERMINAL});
    findNonTerminal(lex::PROG, root, token);
    return root;
}

void ast::PROG(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::PUBLIC, lex::PUBLIC_V, lex::TERMINAL);
    lexemas.emplace_back(lex::CLASS, lex::CLASS_V, lex::TERMINAL);
    lexemas.emplace_back(lex::IDENTIFIER, lex::IDENTIFIER_V, lex::TERMINAL);
    lexemas.emplace_back(lex::ABERTURA_CHAVE, lex::ABERTURA_CHAVE_V, lex::TERMINAL);
    lexemas.emplace_back(lex::INIT, lex::INIT_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::METODO, lex::METODO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::FECHAMENTO_CHAVE, lex::FECHAMENTO_CHAVE_V, lex::TERMINAL);
    isProductionValid(node, token, lexemas);
}

void ast::INIT(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::PUBLIC, lex::PUBLIC_V, lex::TERMINAL);
    lexemas.emplace_back(lex::STATIC, lex::STATIC_V, lex::TERMINAL);
    lexemas.emplace_back(lex::VOID, lex::VOID_V, lex::TERMINAL);
    lexemas.emplace_back(lex::MAIN, lex::MAIN_V, lex::TERMINAL);
    lexemas.emplace_back(lex::ABERTURA_PARENTESE, lex::ABERTURA_PARENTESE_V, lex::TERMINAL);
    lexemas.emplace_back(lex::FECHAMENTO_PARENTESE, lex::FECHAMENTO_PARENTESE_V, lex::TERMINAL);
    lexemas.emplace_back(lex::ABERTURA_CHAVE, lex::ABERTURA_CHAVE_V, lex::TERMINAL);
    lexemas.emplace_back(lex::DC, lex::DC_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::CMDS, lex::CMDS_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::FECHAMENTO_CHAVE, lex::FECHAMENTO_CHAVE_V, lex::TERMINAL);
    isProductionValid(node, token, lexemas);
}

void ast::METODO(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::PUBLIC, lex::PUBLIC_V, lex::TERMINAL);
    lexemas.emplace_back(lex::STATIC, lex::STATIC_V, lex::TERMINAL);
    lexemas.emplace_back(lex::TIPO, lex::TIPO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::IDENTIFIER, lex::IDENTIFIER_V, lex::TERMINAL);
    lexemas.emplace_back(lex::ABERTURA_PARENTESE, lex::ABERTURA_PARENTESE_V, lex::TERMINAL);
    lexemas.emplace_back(lex::PARAMS, lex::PARAMS_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::FECHAMENTO_PARENTESE, lex::FECHAMENTO_PARENTESE_V, lex::TERMINAL);
    lexemas.emplace_back(lex::ABERTURA_CHAVE, lex::ABERTURA_CHAVE_V, lex::TERMINAL);
    lexemas.emplace_back(lex::DC, lex::DC_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::CMDS, lex::CMDS_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::RETURN, lex::RETURN_V, lex::TERMINAL);
    lexemas.emplace_back(lex::EXPRESSAO, lex::EXPRESSAO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::PONTO_VIRGULA, lex::PONTO_VIRGULA_V, lex::TERMINAL);
    lexemas.emplace_back(lex::FECHAMENTO_CHAVE, lex::FECHAMENTO_CHAVE_V, lex::TERMINAL);
    if((*token).value == lex::PUBLIC_V) isProductionValid(node, token, lexemas);
    else node->tokens.push_back(new ast::Node({"VAZIO", "VAZIO", lex::TERMINAL}));
}

void ast::PARAMS(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::TIPO, lex::TIPO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::IDENTIFIER, lex::IDENTIFIER_V, lex::TERMINAL);
    lexemas.emplace_back(lex::MAIS_PARAMS, lex::MAIS_PARAMS_V, lex::NON_TERMINAL);
    if((*token).value == lex::DOUBLE_V) isProductionValid(node, token, lexemas);
    else node->tokens.push_back(new ast::Node({"VAZIO", "VAZIO", lex::TERMINAL}));
}

void ast::MAIS_PARAMS(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::VIRGULA, lex::VIRGULA_V, lex::TERMINAL);
    lexemas.emplace_back(lex::PARAMS, lex::PARAMS_V, lex::NON_TERMINAL);
    if((*token).value == lex::VIRGULA_V) isProductionValid(node, token, lexemas);
    else node->tokens.push_back(new ast::Node({"VAZIO", "VAZIO", lex::TERMINAL}));
}

void ast::DC(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::VAR, lex::VAR_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::MAIS_DC, lex::MAIS_DC_V, lex::NON_TERMINAL);
    if((*token).value == lex::DOUBLE_V) isProductionValid(node, token, lexemas);
    else node->tokens.push_back(new ast::Node({"VAZIO", "VAZIO", lex::TERMINAL}));
}

void ast::MAIS_DC(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::PONTO_VIRGULA, lex::PONTO_VIRGULA_V, lex::TERMINAL);
    lexemas.emplace_back(lex::DC, lex::DC_V, lex::NON_TERMINAL);
    if((*token).value == lex::PONTO_VIRGULA_V) isProductionValid(node, token, lexemas);
    else node->tokens.push_back(new ast::Node({"VAZIO", "VAZIO", lex::TERMINAL}));
}

void ast::VAR(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::TIPO, lex::TIPO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::VARS, lex::VARS_V, lex::NON_TERMINAL);
    isProductionValid(node, token, lexemas);
}

void ast::VARS(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::IDENTIFIER, lex::IDENTIFIER_V, lex::TERMINAL);
    lexemas.emplace_back(lex::MAIS_VAR, lex::MAIS_VAR_V, lex::NON_TERMINAL);
    isProductionValid(node, token, lexemas);
}

void ast::MAIS_VAR(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::VIRGULA, lex::VIRGULA_V, lex::TERMINAL);
    lexemas.emplace_back(lex::VARS, lex::VARS_V, lex::NON_TERMINAL);
    if((*token).value == lex::VIRGULA_V) isProductionValid(node, token, lexemas);
    else node->tokens.push_back(new ast::Node({"VAZIO", "VAZIO", lex::TERMINAL}));
}

void ast::TIPO(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::DOUBLE, lex::DOUBLE_V, lex::TERMINAL);
    isProductionValid(node, token, lexemas);
}

void ast::CMDS(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    if ((*token).type == lex::IDENTIFIER_V || (*token).value == lex::PRINTLN_V) {
        lexemas.emplace_back(lex::CMD, lex::CMD_V, lex::NON_TERMINAL);
        lexemas.emplace_back(lex::PONTO_VIRGULA, lex::PONTO_VIRGULA_V, lex::TERMINAL);
        lexemas.emplace_back(lex::CMDS, lex::CMDS_V, lex::NON_TERMINAL);
    } else if((*token).value == lex::IF_V || (*token).value == lex::WHILE_V) {
        lexemas.emplace_back(lex::CONDITIONAL_CMD, lex::CONDITIONAL_CMD_V, lex::NON_TERMINAL);
        lexemas.emplace_back(lex::CMDS, lex::CMDS_V, lex::NON_TERMINAL);
    } else {
        node->tokens.push_back(new ast::Node({"VAZIO", "VAZIO", lex::TERMINAL}));
        return;
    }
    isProductionValid(node, token, lexemas);
}

void ast::CONDITIONAL_CMD(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    if((*token).value == lex::IF_V) {
        lexemas.emplace_back(lex::IF, lex::IF_V, lex::TERMINAL);
        lexemas.emplace_back(lex::ABERTURA_PARENTESE, lex::ABERTURA_PARENTESE_V, lex::TERMINAL);
        lexemas.emplace_back(lex::CONDICAO, lex::CONDICAO_V, lex::NON_TERMINAL);
        lexemas.emplace_back(lex::FECHAMENTO_PARENTESE, lex::FECHAMENTO_PARENTESE_V, lex::TERMINAL);
        lexemas.emplace_back(lex::ABERTURA_CHAVE, lex::ABERTURA_CHAVE_V, lex::TERMINAL);
        lexemas.emplace_back(lex::CMDS, lex::CMDS_V, lex::NON_TERMINAL);
        lexemas.emplace_back(lex::FECHAMENTO_CHAVE, lex::FECHAMENTO_CHAVE_V, lex::TERMINAL);
        lexemas.emplace_back(lex::PFALSA, lex::PFALSA_V, lex::NON_TERMINAL);
    } else if((*token).value == lex::WHILE_V) {
        lexemas.emplace_back(lex::WHILE, lex::WHILE_V, lex::TERMINAL);
        lexemas.emplace_back(lex::ABERTURA_PARENTESE, lex::ABERTURA_PARENTESE_V, lex::TERMINAL);
        lexemas.emplace_back(lex::CONDICAO, lex::CONDICAO_V, lex::NON_TERMINAL);
        lexemas.emplace_back(lex::FECHAMENTO_PARENTESE, lex::FECHAMENTO_PARENTESE_V, lex::TERMINAL);
        lexemas.emplace_back(lex::ABERTURA_CHAVE, lex::ABERTURA_CHAVE_V, lex::TERMINAL);
        lexemas.emplace_back(lex::CMDS, lex::CMDS_V, lex::NON_TERMINAL);
        lexemas.emplace_back(lex::FECHAMENTO_CHAVE, lex::FECHAMENTO_CHAVE_V, lex::TERMINAL);
    }
    isProductionValid(node, token, lexemas);
}

void ast::CMD(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    if((*token).value == lex::PRINTLN_V) {
        lexemas.emplace_back(lex::PRINTLN, lex::PRINTLN_V, lex::TERMINAL);
        lexemas.emplace_back(lex::ABERTURA_PARENTESE, lex::ABERTURA_PARENTESE_V, lex::TERMINAL);
        lexemas.emplace_back(lex::EXPRESSAO, lex::EXPRESSAO_V, lex::NON_TERMINAL);
        lexemas.emplace_back(lex::FECHAMENTO_PARENTESE, lex::FECHAMENTO_PARENTESE_V, lex::TERMINAL);
    } else if((*token).type == lex::IDENTIFIER_V) {
        lexemas.emplace_back(lex::IDENTIFIER, lex::IDENTIFIER_V, lex::TERMINAL);
        lexemas.emplace_back(lex::RESTO_IDENT, lex::RESTO_IDENT_V, lex::NON_TERMINAL);
    }
    isProductionValid(node, token, lexemas);
}

void ast::PFALSA(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::ELSE, lex::ELSE_V, lex::TERMINAL);
    lexemas.emplace_back(lex::ABERTURA_CHAVE, lex::ABERTURA_CHAVE_V, lex::TERMINAL);
    lexemas.emplace_back(lex::CMDS, lex::CMDS_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::FECHAMENTO_CHAVE, lex::FECHAMENTO_CHAVE_V, lex::TERMINAL);
    if((*token).value == lex::ELSE_V) isProductionValid(node, token, lexemas);
    else node->tokens.push_back(new ast::Node({"VAZIO", "VAZIO", lex::TERMINAL}));
}


void ast::RESTO_IDENT(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    if((*token).value == lex::ATRIBUICAO_V) {
        lexemas.emplace_back(lex::ATRIBUICAO, lex::ATRIBUICAO_V, lex::TERMINAL);
        lexemas.emplace_back(lex::EXP_IDENT, lex::EXP_IDENT_V, lex::NON_TERMINAL);
    } else if((*token).value == lex::ABERTURA_PARENTESE_V) {
        lexemas.emplace_back(lex::ABERTURA_PARENTESE, lex::ABERTURA_PARENTESE_V, lex::TERMINAL);
        lexemas.emplace_back(lex::LISTA_ARG, lex::LISTA_ARG_V, lex::NON_TERMINAL);
        lexemas.emplace_back(lex::FECHAMENTO_PARENTESE, lex::FECHAMENTO_PARENTESE_V, lex::TERMINAL);
    } else {
        return;
    }
    isProductionValid(node, token, lexemas);
}

void ast::LISTA_ARG(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::ARGUMENTOS, lex::ARGUMENTOS_V, lex::NON_TERMINAL);
    if((*token).type == lex::IDENTIFIER_V) isProductionValid(node, token, lexemas);
    else node->tokens.push_back(new ast::Node({"VAZIO", "VAZIO", lex::TERMINAL}));
}

void ast::ARGUMENTOS(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::IDENTIFIER, lex::IDENTIFIER_V, lex::TERMINAL);
    lexemas.emplace_back(lex::MAIS_IDENT, lex::MAIS_IDENT_V, lex::NON_TERMINAL);
    if((*token).type == lex::IDENTIFIER_V) isProductionValid(node, token, lexemas);
}

void ast::MAIS_IDENT(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::VIRGULA, lex::VIRGULA_V, lex::TERMINAL);
    lexemas.emplace_back(lex::ARGUMENTOS, lex::ARGUMENTOS_V, lex::NON_TERMINAL);
    if((*token).value == lex::VIRGULA_V) isProductionValid(node, token, lexemas);
    else node->tokens.push_back(new ast::Node({"VAZIO", "VAZIO", lex::TERMINAL}));
}

void ast::EXP_IDENT(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::EXPRESSAO, lex::EXPRESSAO_V, lex::NON_TERMINAL);
    if( (*token).type == lex::IDENTIFIER_V ||
        (*token).type == lex::NUM_V ||
        (*token).value == lex::ABERTURA_PARENTESE_V ||
        (*token).value == lex::SUBTRACAO_V) {
        isProductionValid(node, token, lexemas);
    } else if((*token).value == lex::LER_DOUBLE_V) {
        node->tokens.push_back(new Node(token->type, token->value, lex::TERMINAL));
        token++;
    }
}

void ast::CONDICAO(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::EXPRESSAO, lex::EXPRESSAO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::RELACAO, lex::RELACAO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::EXPRESSAO, lex::EXPRESSAO_V, lex::NON_TERMINAL);
    if ((*token).type == lex::IDENTIFIER_V || (*token).type == lex::NUM_V ||
        (*token).value == lex::ABERTURA_PARENTESE_V || (*token).value == lex::SUBTRACAO_V) {
        isProductionValid(node, token, lexemas);
    }
}

void ast::RELACAO(ast::Node* node, std::vector<lex::token>::iterator & token) {
    if((*token).type == "Operator") {
        node->tokens.push_back(new Node(token->type, token->value, lex::TERMINAL));
        token++;
    }
}

void ast::EXPRESSAO(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::TERMO, lex::TERMO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::OUTROS_TERMOS, lex::OUTROS_TERMOS_V, lex::NON_TERMINAL);
    if ((*token).type == lex::IDENTIFIER_V || (*token).type == lex::NUM_V ||
        (*token).value == lex::ABERTURA_PARENTESE_V || (*token).value == lex::SUBTRACAO_V) {
        isProductionValid(node, token, lexemas);
    }
}

void ast::TERMO(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::OP_UN, lex::OP_UN_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::FATOR, lex::FATOR_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::MAIS_FATORES, lex::MAIS_FATORES_V, lex::NON_TERMINAL);
    if ((*token).type == lex::IDENTIFIER_V || (*token).type == lex::NUM_V ||
        (*token).value == lex::ABERTURA_PARENTESE_V || (*token).value == lex::SUBTRACAO_V) {
        isProductionValid(node, token, lexemas);
    }
}

void ast::OP_UN(ast::Node* node, std::vector<lex::token>::iterator & token) {
    if((*token).value == lex::NEGACAO_V) {
        node->tokens.push_back(new Node(token->type, token->value, lex::TERMINAL));
        token++;
    } else node->tokens.push_back(new ast::Node({"VAZIO", "VAZIO", lex::TERMINAL}));
}

void ast::FATOR(ast::Node* node, std::vector<lex::token>::iterator & token) {
    if((*token).type == lex::IDENTIFIER_V || (*token).type == lex::NUM_V) {
        node->tokens.push_back(new Node(token->type, token->value, lex::TERMINAL));
        token++;
    }
}

void ast::OUTROS_TERMOS(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::OP_AD, lex::OP_AD_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::TERMO, lex::TERMO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::OUTROS_TERMOS, lex::OUTROS_TERMOS_V, lex::NON_TERMINAL);
    if((*token).value == lex::ADICAO_V || (*token).value == lex::SUBTRACAO_V) isProductionValid(node, token, lexemas);
    else node->tokens.push_back(new ast::Node({"VAZIO", "VAZIO", lex::TERMINAL}));
}

void ast::OP_AD(ast::Node* node, std::vector<lex::token>::iterator & token) {
    if((*token).value == lex::ADICAO_V || (*token).value == lex::SUBTRACAO_V) {
        node->tokens.push_back(new Node(token->type, token->value, lex::TERMINAL));
        token++;
    }
}

void ast::MAIS_FATORES(ast::Node* node, std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::OP_MUL, lex::OP_MUL_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::FATOR, lex::FATOR_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::MAIS_FATORES, lex::MAIS_FATORES_V, lex::NON_TERMINAL);
    if((*token).value == lex::MULTIPLICACAO_V || (*token).value == lex::DIVISAO_V) isProductionValid(node, token, lexemas);
    else node->tokens.push_back(new ast::Node({"VAZIO", "VAZIO", lex::TERMINAL}));
}

void ast::OP_MUL(ast::Node* node, std::vector<lex::token>::iterator & token) {
    if((*token).value == lex::MULTIPLICACAO_V || (*token).value == lex::DIVISAO_V) {
        node->tokens.push_back(new Node(token->type, token->value, lex::TERMINAL));
        token++;
    }
}
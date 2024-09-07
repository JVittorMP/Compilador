#include "sin.h"

int findNonTerminal(unsigned lexema_type, std::vector<lex::token>::iterator & token) {
    switch (lexema_type) {
        case lex::PROG :
            if(sin::PROG(token)) return SUCCESS;
            return FAIL;
        case lex::INIT :
            if(sin::INIT(token)) return SUCCESS;
            return FAIL;
        case lex::METODO:
            if(sin::METODO(token)) return SUCCESS;
            return FAIL;
        case lex::PARAMS:
            if(sin::PARAMS(token)) return SUCCESS;
            return FAIL;
        case lex::MAIS_PARAMS:
            if(sin::MAIS_PARAMS(token)) return SUCCESS;
            return FAIL;
        case lex::DC:
            if(sin::DC(token)) return SUCCESS;
            return FAIL;
        case lex::MAIS_DC:
            if(sin::MAIS_DC(token)) return SUCCESS;
            return FAIL;
        case lex::VAR:
            if(sin::VAR(token)) return SUCCESS;
            return FAIL;
        case lex::VARS:
            if(sin::VARS(token)) return SUCCESS;
            return FAIL;
        case lex::MAIS_VAR:
            if(sin::MAIS_VAR(token)) return SUCCESS;
            return FAIL;
        case lex::TIPO:
            if(sin::TIPO(token)) return SUCCESS;
            return FAIL;
        case lex::CMDS:
            if(sin::CMDS(token)) return SUCCESS;
            return FAIL;
        case lex::CONDITIONAL_CMD:
            if(sin::CONDITIONAL_CMD(token)) return SUCCESS;
            return FAIL;
        case lex::CMD:
            if(sin::CMD(token)) return SUCCESS;
            return FAIL;
        case lex::PFALSA:
            if(sin::PFALSA(token)) return SUCCESS;
            return FAIL;
        case lex::RESTO_IDENT:
            if(sin::RESTO_IDENT(token)) return SUCCESS;
            return FAIL;
        case lex::LISTA_ARG:
            if(sin::LISTA_ARG(token)) return SUCCESS;
            return FAIL;
        case lex::ARGUMENTOS:
            if(sin::ARGUMENTOS(token)) return SUCCESS;
            return FAIL;
        case lex::MAIS_IDENT:
            if(sin::MAIS_IDENT(token)) return SUCCESS;
            return FAIL;
        case lex::EXP_IDENT:
            if(sin::EXP_IDENT(token)) return SUCCESS;
            return FAIL;
        case lex::CONDICAO:
            if(sin::CONDICAO(token)) return SUCCESS;
            return FAIL;
        case lex::RELACAO:
            if(sin::RELACAO(token)) return SUCCESS;
            return FAIL;
        case lex::EXPRESSAO:
            if(sin::EXPRESSAO(token)) return SUCCESS;
            return FAIL;
        case lex::TERMO:
            if(sin::TERMO(token)) return SUCCESS;
            return FAIL;
        case lex::OP_UN:
            if(sin::OP_UN(token)) return SUCCESS;
            return FAIL;
        case lex::FATOR:
            if(sin::FATOR(token)) return SUCCESS;
            return FAIL;
        case lex::OUTROS_TERMOS:
            if(sin::OUTROS_TERMOS(token)) return SUCCESS;
            return FAIL;
        case lex::OP_AD:
            if(sin::OP_AD(token)) return SUCCESS;
            return FAIL;
        case lex::MAIS_FATORES:
            if(sin::MAIS_FATORES(token)) return SUCCESS;
            return FAIL;
        case lex::OP_MUL:
            if(sin::OP_MUL(token)) return SUCCESS;
            return FAIL;
        default:
            return FAIL;
    }
}

int isProductionValid(std::vector<lex::token>::iterator & token, std::vector<lex::lexema> & lexemas) {
    for(auto & lexema : lexemas) {
        if((*token).value == "$") return FAIL;
        if(lexema.terminal) {
            if(lexema.value == lex::IDENTIFIER_V && (*token).type == lex::IDENTIFIER_V) {
                // std::cout << lex::IDENTIFIER_V << std::endl;
            } else if(lexema.value != (*token).value) return FAIL;
            token++;
        } else {
            if(!findNonTerminal(lexema.type, token)) return FAIL;
        }
    }
    return SUCCESS;
}

int sin::parse(std::vector<lex::token>::iterator & token) {
    return findNonTerminal(0, token);
}

int sin::PROG(std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::PUBLIC, lex::PUBLIC_V, lex::TERMINAL);
    lexemas.emplace_back(lex::CLASS, lex::CLASS_V, lex::TERMINAL);
    lexemas.emplace_back(lex::IDENTIFIER, lex::IDENTIFIER_V, lex::TERMINAL);
    lexemas.emplace_back(lex::ABERTURA_CHAVE, lex::ABERTURA_CHAVE_V, lex::TERMINAL);
    lexemas.emplace_back(lex::INIT, lex::INIT_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::METODO, lex::METODO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::FECHAMENTO_CHAVE, lex::FECHAMENTO_CHAVE_V, lex::TERMINAL);
    if(isProductionValid(token, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::INIT(std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::PUBLIC, lex::PUBLIC_V, lex::TERMINAL);
    lexemas.emplace_back(lex::STATIC, lex::STATIC_V, lex::TERMINAL);
    lexemas.emplace_back(lex::VOID, lex::VOID_V, lex::TERMINAL);
    lexemas.emplace_back(lex::MAIN, lex::MAIN_V, lex::TERMINAL);
    lexemas.emplace_back(lex::ABERTURA_PARENTESE, lex::ABERTURA_PARENTESE_V, lex::TERMINAL);
    //lexemas.emplace_back(lex::STRING, lex::STRING_V, lex::TERMINAL);
    //lexemas.emplace_back(lex::ABERTURA_COLCHETE, lex::ABERTURA_COLCHETE_V, lex::TERMINAL);
    //lexemas.emplace_back(lex::FECHAMENTO_COLCHETE, lex::FECHAMENTO_COLCHETE_V,lex::TERMINAL);
    //lexemas.emplace_back(lex::IDENTIFIER, lex::IDENTIFIER_V, lex::TERMINAL);
    lexemas.emplace_back(lex::FECHAMENTO_PARENTESE, lex::FECHAMENTO_PARENTESE_V, lex::TERMINAL);
    lexemas.emplace_back(lex::ABERTURA_CHAVE, lex::ABERTURA_CHAVE_V, lex::TERMINAL);
    lexemas.emplace_back(lex::DC, lex::DC_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::CMDS, lex::CMDS_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::FECHAMENTO_CHAVE, lex::FECHAMENTO_CHAVE_V, lex::TERMINAL);
    if(isProductionValid(token, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::METODO(std::vector<lex::token>::iterator &token) {
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
    if((*token).value == lex::PUBLIC_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return SUCCESS;
}

int sin::PARAMS(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::TIPO, lex::TIPO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::IDENTIFIER, lex::IDENTIFIER_V, lex::TERMINAL);
    lexemas.emplace_back(lex::MAIS_PARAMS, lex::MAIS_PARAMS_V, lex::NON_TERMINAL);
    if((*token).value == lex::DOUBLE_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return SUCCESS;
}

int sin::MAIS_PARAMS(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::VIRGULA, lex::VIRGULA_V, lex::TERMINAL);
    lexemas.emplace_back(lex::PARAMS, lex::PARAMS_V, lex::NON_TERMINAL);
    if((*token).value == lex::VIRGULA_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return SUCCESS;
}

int sin::DC(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::VAR, lex::VAR_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::MAIS_DC, lex::MAIS_DC_V, lex::NON_TERMINAL);
    if((*token).value == lex::DOUBLE_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return SUCCESS;
}

int sin::MAIS_DC(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::PONTO_VIRGULA, lex::PONTO_VIRGULA_V, lex::TERMINAL);
    lexemas.emplace_back(lex::DC, lex::DC_V, lex::NON_TERMINAL);
    if((*token).value == lex::PONTO_VIRGULA_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return SUCCESS;
}

int sin::VAR(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::TIPO, lex::TIPO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::VARS, lex::VARS_V, lex::NON_TERMINAL);
    if(isProductionValid(token, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::VARS(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::IDENTIFIER, lex::IDENTIFIER_V, lex::TERMINAL);
    lexemas.emplace_back(lex::MAIS_VAR, lex::MAIS_VAR_V, lex::NON_TERMINAL);
    if(isProductionValid(token, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::MAIS_VAR(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::VIRGULA, lex::VIRGULA_V, lex::TERMINAL);
    lexemas.emplace_back(lex::VARS, lex::VARS_V, lex::NON_TERMINAL);
    if((*token).value == lex::VIRGULA_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return SUCCESS;
}

int sin::TIPO(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::DOUBLE, lex::DOUBLE_V, lex::TERMINAL);
    if(isProductionValid(token, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::CMDS(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    if ((*token).type == lex::IDENTIFIER_V || (*token).value == lex::PRINTLN_V) {
        lexemas.emplace_back(lex::CMD, lex::CMD_V, lex::NON_TERMINAL);
        lexemas.emplace_back(lex::PONTO_VIRGULA, lex::PONTO_VIRGULA_V, lex::TERMINAL);
        lexemas.emplace_back(lex::CMDS, lex::CMDS_V, lex::NON_TERMINAL);
    } else if((*token).value == lex::IF_V || (*token).value == lex::WHILE_V) {
        lexemas.emplace_back(lex::CONDITIONAL_CMD, lex::CONDITIONAL_CMD_V, lex::NON_TERMINAL);
        lexemas.emplace_back(lex::CMDS, lex::CMDS_V, lex::NON_TERMINAL);
    } else {
        return SUCCESS;
    }
    if(isProductionValid(token, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::CONDITIONAL_CMD(std::vector<lex::token>::iterator &token) {
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
    } else {
        return FAIL;
    }
    if(isProductionValid(token, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::CMD(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    if((*token).value == lex::PRINTLN_V) {
        lexemas.emplace_back(lex::PRINTLN, lex::PRINTLN_V, lex::TERMINAL);
        lexemas.emplace_back(lex::ABERTURA_PARENTESE, lex::ABERTURA_PARENTESE_V, lex::TERMINAL);
        lexemas.emplace_back(lex::EXPRESSAO, lex::EXPRESSAO_V, lex::NON_TERMINAL);
        lexemas.emplace_back(lex::FECHAMENTO_PARENTESE, lex::FECHAMENTO_PARENTESE_V, lex::TERMINAL);
    } else if((*token).type == lex::IDENTIFIER_V) {
        lexemas.emplace_back(lex::IDENTIFIER, lex::IDENTIFIER_V, lex::TERMINAL);
        lexemas.emplace_back(lex::RESTO_IDENT, lex::RESTO_IDENT_V, lex::NON_TERMINAL);
    } else {
        return FAIL;
    }
    if(isProductionValid(token, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::PFALSA(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::ELSE, lex::ELSE_V, lex::TERMINAL);
    lexemas.emplace_back(lex::ABERTURA_CHAVE, lex::ABERTURA_CHAVE_V, lex::TERMINAL);
    lexemas.emplace_back(lex::CMDS, lex::CMDS_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::FECHAMENTO_CHAVE, lex::FECHAMENTO_CHAVE_V, lex::TERMINAL);
    if((*token).value == lex::ELSE_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return SUCCESS;
}


int sin::RESTO_IDENT(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    if((*token).value == lex::ATRIBUICAO_V) {
        lexemas.emplace_back(lex::ATRIBUICAO, lex::ATRIBUICAO_V, lex::TERMINAL);
        lexemas.emplace_back(lex::EXP_IDENT, lex::EXP_IDENT_V, lex::NON_TERMINAL);
    } else if((*token).value == lex::ABERTURA_PARENTESE_V) {
        lexemas.emplace_back(lex::ABERTURA_PARENTESE, lex::ABERTURA_PARENTESE_V, lex::TERMINAL);
        lexemas.emplace_back(lex::LISTA_ARG, lex::LISTA_ARG_V, lex::NON_TERMINAL);
        lexemas.emplace_back(lex::FECHAMENTO_PARENTESE, lex::FECHAMENTO_PARENTESE_V, lex::TERMINAL);
    } else {
        return FAIL;
    }
    if(isProductionValid(token, lexemas)) return SUCCESS;
    return FAIL;
}

int sin::LISTA_ARG(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::ARGUMENTOS, lex::ARGUMENTOS_V, lex::NON_TERMINAL);
    if((*token).type == lex::IDENTIFIER_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return SUCCESS;
}

int sin::ARGUMENTOS(std::vector<lex::token>::iterator & token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::IDENTIFIER, lex::IDENTIFIER_V, lex::TERMINAL);
    lexemas.emplace_back(lex::MAIS_IDENT, lex::MAIS_IDENT_V, lex::NON_TERMINAL);
    if((*token).type == lex::IDENTIFIER_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
    }
    return FAIL;
}

int sin::MAIS_IDENT(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::VIRGULA, lex::VIRGULA_V, lex::TERMINAL);
    lexemas.emplace_back(lex::ARGUMENTOS, lex::ARGUMENTOS_V, lex::NON_TERMINAL);
    if((*token).value == lex::VIRGULA_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return SUCCESS;
}

int sin::EXP_IDENT(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::EXPRESSAO, lex::EXPRESSAO_V, lex::NON_TERMINAL);
    if( (*token).type == lex::IDENTIFIER_V ||
        (*token).type == lex::NUM_V ||
        (*token).value == lex::ABERTURA_PARENTESE_V ||
        (*token).value == lex::SUBTRACAO_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    } else if((*token).value == lex::LER_DOUBLE_V) {
        token++;
        return SUCCESS;
    }
    return FAIL;
}

int sin::CONDICAO(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::EXPRESSAO, lex::EXPRESSAO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::RELACAO, lex::RELACAO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::EXPRESSAO, lex::EXPRESSAO_V, lex::NON_TERMINAL);
    if ((*token).type == lex::IDENTIFIER_V ||
        (*token).type == lex::NUM_V ||
        (*token).value == lex::ABERTURA_PARENTESE_V ||
        (*token).value == lex::SUBTRACAO_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return FAIL;
}

int sin::RELACAO(std::vector<lex::token>::iterator &token) {
    if((*token).type == "Operator") {
        token++;
        return SUCCESS;
    }
    return FAIL;
}

int sin::EXPRESSAO(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::TERMO, lex::TERMO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::OUTROS_TERMOS, lex::OUTROS_TERMOS_V, lex::NON_TERMINAL);
    if ((*token).type == lex::IDENTIFIER_V ||
        (*token).type == lex::NUM_V ||
        (*token).value == lex::ABERTURA_PARENTESE_V ||
        (*token).value == lex::SUBTRACAO_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return FAIL;
}

int sin::TERMO(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::OP_UN, lex::OP_UN_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::FATOR, lex::FATOR_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::MAIS_FATORES, lex::MAIS_FATORES_V, lex::NON_TERMINAL);
    if( (*token).type == lex::IDENTIFIER_V ||
        (*token).type == lex::NUM_V ||
        (*token).value == lex::ABERTURA_PARENTESE_V ||
        (*token).value == lex::SUBTRACAO_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return FAIL;
}

int sin::OP_UN(std::vector<lex::token>::iterator &token) {
    if((*token).value == lex::NEGACAO_V) token++;
    return SUCCESS;
}

int sin::FATOR(std::vector<lex::token>::iterator &token) {
    if((*token).type == lex::IDENTIFIER_V || (*token).type == lex::NUM_V) {
        token++;
        return SUCCESS;
    }
    return FAIL;
}

int sin::OUTROS_TERMOS(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::OP_AD, lex::OP_AD_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::TERMO, lex::TERMO_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::OUTROS_TERMOS, lex::OUTROS_TERMOS_V, lex::NON_TERMINAL);
    if((*token).value == lex::ADICAO_V || (*token).value == lex::SUBTRACAO_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return SUCCESS;
}

int sin::OP_AD(std::vector<lex::token>::iterator &token) {
    if((*token).value == lex::ADICAO_V || (*token).value == lex::SUBTRACAO_V) {
        token++;
        return SUCCESS;
    }
    return FAIL;
}

int sin::MAIS_FATORES(std::vector<lex::token>::iterator &token) {
    std::vector<lex::lexema> lexemas;
    lexemas.emplace_back(lex::OP_MUL, lex::OP_MUL_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::FATOR, lex::FATOR_V, lex::NON_TERMINAL);
    lexemas.emplace_back(lex::MAIS_FATORES, lex::MAIS_FATORES_V, lex::NON_TERMINAL);
    if((*token).value == lex::MULTIPLICACAO_V || (*token).value == lex::DIVISAO_V) {
        if(isProductionValid(token, lexemas)) return SUCCESS;
        return FAIL;
    }
    return SUCCESS;
}

int sin::OP_MUL(std::vector<lex::token>::iterator &token) {
    if((*token).value == lex::MULTIPLICACAO_V || (*token).value == lex::DIVISAO_V) {
        token++;
        return SUCCESS;
    }
    return FAIL;
}
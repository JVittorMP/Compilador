#ifndef COMPILADORES_SIN_H
#define COMPILADORES_SIN_H

#include "../basic.h"
#include "../Lexer/lex.h"

namespace sin {
    int PROG(std::vector<lex::token>::iterator & tokens);
    int INIT(std::vector<lex::token>::iterator & tokens);
    int METODO(std::vector<lex::token>::iterator & tokens);
    int PARAMS(std::vector<lex::token>::iterator & tokens);
    int MAIS_PARAMS(std::vector<lex::token>::iterator & tokens);
    int DC(std::vector<lex::token>::iterator & tokens);
    int MAIS_DC(std::vector<lex::token>::iterator & tokens);
    int VAR(std::vector<lex::token>::iterator & tokens);
    int VARS(std::vector<lex::token>::iterator & tokens);
    int MAIS_VAR(std::vector<lex::token>::iterator & tokens);
    int TIPO(std::vector<lex::token>::iterator & tokens);
    int CMDS(std::vector<lex::token>::iterator & tokens);
    int CONDITIONAL_CMD(std::vector<lex::token>::iterator & tokens);
    int CMD(std::vector<lex::token>::iterator & tokens);
    int PFALSA(std::vector<lex::token>::iterator & tokens);
    int RESTO_IDENT(std::vector<lex::token>::iterator & tokens);
    int LISTA_ARG(std::vector<lex::token>::iterator & tokens);
    int ARGUMENTOS(std::vector<lex::token>::iterator & tokens);
    int MAIS_IDENT(std::vector<lex::token>::iterator & tokens);
    int EXP_IDENT(std::vector<lex::token>::iterator & tokens);
    int CONDICAO(std::vector<lex::token>::iterator & tokens);
    int RELACAO(std::vector<lex::token>::iterator & tokens);
    int EXPRESSAO(std::vector<lex::token>::iterator & tokens);
    int TERMO(std::vector<lex::token>::iterator & tokens);
    int OP_UN(std::vector<lex::token>::iterator & tokens);
    int FATOR(std::vector<lex::token>::iterator & tokens);
    int OUTROS_TERMOS(std::vector<lex::token>::iterator & tokens);
    int OP_AD(std::vector<lex::token>::iterator & tokens);
    int MAIS_FATORES(std::vector<lex::token>::iterator & tokens);
    int OP_MUL(std::vector<lex::token>::iterator & tokens);

    int parse(std::vector<lex::token>::iterator & tokens);
}

#endif

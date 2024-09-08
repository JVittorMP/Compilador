#ifndef COMPILADORES_LEX_H
#define COMPILADORES_LEX_H

namespace lex {

    typedef struct lexema {
    public:
        unsigned type;
        std::string value;
        bool terminal;

        lexema() = default;
        lexema(unsigned type, std::string value, bool terminal):
            type(type), value(std::move(value)), terminal(terminal) {}

    } lexema;

    const bool TERMINAL = true;
    const bool NON_TERMINAL = false;

    const std::string PROG_V = "PROG";
    const std::string INIT_V = "INIT";
    const std::string PUBLIC_V = "public";
    const std::string CLASS_V = "class";
    const std::string IDENTIFIER_V = "Identifier";
    const std::string ABERTURA_CHAVE_V = "{";
    const std::string FECHAMENTO_CHAVE_V = "}";
    const std::string STATIC_V = "static";
    const std::string VOID_V = "void";
    const std::string MAIN_V = "main";
    const std::string ABERTURA_PARENTESE_V = "(";
    const std::string FECHAMENTO_PARENTESE_V = ")";
    const std::string STRING_V = "String";
    const std::string ABERTURA_COLCHETE_V = "[";
    const std::string FECHAMENTO_COLCHETE_V = "]";
    const std::string CMDS_V = "CMDS";
    const std::string METODO_V = "METODO";
    const std::string TIPO_V = "TIPO";
    const std::string PARAMS_V = "PARAMS";
    const std::string DC_V = "DC";
    const std::string RETURN_V = "return";
    const std::string EXPRESSAO_V = "EXPRESSAO";
    const std::string PONTO_VIRGULA_V = ";";
    const std::string VIRGULA_V = ",";
    const std::string SUBTRACAO_V = "-";
    const std::string ADICAO_V = "+";
    const std::string DIVISAO_V = "/";
    const std::string MULTIPLICACAO_V = "*";
    const std::string NEGACAO_V = "-";
    const std::string ATRIBUICAO_V = "=";
    const std::string IGUAL_V = "==";
    const std::string DIFERENTE_V = "!=";
    const std::string MAIOR_IGUAL_V = ">=";
    const std::string MENOR_IGUAL_V = "<=";
    const std::string MAIOR_V = ">";
    const std::string MENOR_V = "<";
    const std::string NUM_V = "Num";
    const std::string DOUBLE_V = "double";
    const std::string MAIS_PARAMS_V = "MAIS_PARAMS";
    const std::string MAIS_VAR_V = "MAIS_VAR";
    const std::string VARS_V = "VARS";
    const std::string IF_V = "if";
    const std::string ELSE_V = "else";
    const std::string WHILE_V = "while";
    const std::string CONDICAO_V = "CONDICAO";
    const std::string PFALSA_V = "PFALSA";
    const std::string PRINTLN_V = "System.out.println";
    const std::string RESTO_IDENT_V = "RESTO_IDENT";
    const std::string LISTA_ARG_V = "LISTA_ARG";
    const std::string MAIS_IDENT_V = "MAIS_IDENT";
    const std::string ARGUMENTOS_V = "ARGUMENTOS";
    const std::string LER_DOUBLE_V = "lerDouble()";
    const std::string VAR_V = "VAR";
    const std::string MAIS_DC_V = "MAIS_DC";
    const std::string CONDITIONAL_CMD_V = "CONDITIONAL_CMD";
    const std::string CMD_V = "CMD";
    const std::string RELACAO_V = "RELACAO";
    const std::string TERMO_V = "TERMO";
    const std::string OP_UN_V = "OP_UN";
    const std::string OP_AD_V = "OP_AD";
    const std::string OP_MUL_V = "OP_MUL";
    const std::string FATOR_V = "FATOR";
    const std::string MAIS_FATORES_V = "MAIS_FATORES";
    const std::string OUTROS_TERMOS_V = "OUTROS_TERMOS";
    const std::string EXP_IDENT_V = "EXP_IDENT";
    const std::string VAZIO_V = "VAZIO";

    const unsigned PROG = 0;
    const unsigned PUBLIC = 1;
    const unsigned CLASS = 2;
    const unsigned IDENTIFIER = 3;
    const unsigned ABERTURA_CHAVE = 4;
    const unsigned FECHAMENTO_CHAVE = 5;
    const unsigned STATIC = 6;
    const unsigned VOID = 7;
    const unsigned MAIN = 8;
    const unsigned ABERTURA_PARENTESE = 9;
    const unsigned FECHAMENTO_PARENTESE = 10;
    const unsigned STRING = 11;
    const unsigned ABERTURA_COLCHETE = 12;
    const unsigned FECHAMENTO_COLCHETE = 13;
    const unsigned CMDS = 14;
    const unsigned METODO = 15;
    const unsigned TIPO = 16;
    const unsigned PARAMS = 17;
    const unsigned DC = 18;
    const unsigned RETURN = 19;
    const unsigned EXPRESSAO = 20;
    const unsigned PONTO_VIRGULA = 21;
    const unsigned VIRGULA = 22;
    const unsigned SUBTRACAO = 23;
    const unsigned ADICAO = 24;
    const unsigned DIVISAO = 25;
    const unsigned MULTIPLICACAO = 26;
    const unsigned NEGACAO = 27;
    const unsigned ATRIBUICAO = 28;
    const unsigned IGUAL = 29;
    const unsigned DIFERENTE = 30;
    const unsigned MAIOR_IGUAL = 31;
    const unsigned MENOR_IGUAL = 32;
    const unsigned MAIOR = 33;
    const unsigned MENOR = 34;
    const unsigned NUM = 35;
    const unsigned DOUBLE = 36;
    const unsigned MAIS_PARAMS = 37;
    const unsigned MAIS_VAR = 38;
    const unsigned VARS = 39;
    const unsigned IF = 40;
    const unsigned ELSE = 41;
    const unsigned WHILE = 42;
    const unsigned CONDICAO = 43;
    const unsigned PFALSA = 44;
    const unsigned PRINTLN = 45;
    const unsigned RESTO_IDENT = 46;
    const unsigned LISTA_ARG = 47;
    const unsigned MAIS_IDENT = 48;
    const unsigned ARGUMENTOS = 49;
    const unsigned LER_DOUBLE = 50;
    const unsigned VAR = 51;
    const unsigned MAIS_DC = 52;
    const unsigned CONDITIONAL_CMD = 53;
    const unsigned CMD = 54;
    const unsigned RELACAO = 55;
    const unsigned TERMO = 56;
    const unsigned OP_UN = 57;
    const unsigned OP_AD = 58;
    const unsigned OP_MUL = 59;
    const unsigned FATOR = 60;
    const unsigned MAIS_FATORES = 61;
    const unsigned OUTROS_TERMOS = 62;
    const unsigned EXP_IDENT = 63;
    const unsigned VAZIO = 64;
    const unsigned INIT = 65;

    typedef struct token {
    public:
        std::string type;
        std::string value;
        unsigned linha = 0;

        token() = default;
        token(std::string type, std::string value, unsigned line): type(std::move(type)), value(std::move(value)), linha(line) {}

        bool operator==(const token & token) const {
            return std::tie(this->type, this->value) == std::tie(token.type, token.value);
        }
    } token;
}

#endif
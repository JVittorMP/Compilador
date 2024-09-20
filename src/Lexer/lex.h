#ifndef COMPILADORES_LEX_H
#define COMPILADORES_LEX_H

#include "../basic.h"

namespace lex {
    constexpr bool TERMINAL = true;
    constexpr bool NON_TERMINAL = false;

    class Type {
    public:
        enum class pattern {
            OPERATOR,
            KEYWORD,
            PUNCTUATION,
            SIGNATURE,
            PARAM,

            PROG,
            INIT,
            PUBLIC,
            CLASS,
            IDENTIFIER,
            LCHAVE,
            RCHAVE,
            STATIC,
            VOID,
            MAIN,
            LPARENTESE,
            RPARENTESE,
            STRING,
            LCOLCHETE,
            RCOLCHETE,
            CMDS,
            METODO,
            TIPO,
            PARAMS,
            DC,
            RETURN,
            EXPRESSAO,
            PONTO_VIRGULA,
            VIRGULA,
            SUBTRACAO,
            ADICAO,
            DIVISAO,
            MULTIPLICACAO,
            NEGACAO,
            ATRIBUICAO,
            IGUAL,
            DIFERENTE,
            MAIOR_IGUAL,
            MENOR_IGUAL,
            MAIOR,
            MENOR,
            NUM,
            DOUBLE,
            MAIS_PARAMS,
            MAIS_VAR,
            VARS,
            IF,
            ELSE,
            WHILE,
            CONDICAO,
            PFALSA,
            OUTPUT,
            RESTO_IDENT,
            LISTA_ARG,
            MAIS_IDENT,
            ARGUMENTOS,
            INPUT,
            VAR,
            MAIS_DC,
            CONDITIONAL_CMD,
            CMD,
            RELACAO,
            TERMO,
            OP_UN,
            OP_AD,
            OP_MUL,
            FATOR,
            MAIS_FATORES,
            OUTROS_TERMOS,
            EXP_IDENT,
            END,
            VAZIO,
            ERROR
        };

    private:
        static std::string enumToString(pattern p) {
            switch(p) {
                case pattern::OPERATOR: return "Operator";
                case pattern::KEYWORD: return "Keyword";
                case pattern::PUNCTUATION: return "Punctuation";
                case pattern::SIGNATURE: return "SIGNATURE";
                case pattern::PARAM: return "PARAM";

                case pattern::PROG: return "PROG";
                case pattern::INIT: return "INIT";
                case pattern::PUBLIC: return "public";
                case pattern::CLASS: return "class";
                case pattern::IDENTIFIER: return "Identifier";
                case pattern::LCHAVE: return "{";
                case pattern::RCHAVE: return "}";
                case pattern::STATIC: return "static";
                case pattern::VOID: return "void";
                case pattern::MAIN: return "main";
                case pattern::LPARENTESE: return "(";
                case pattern::RPARENTESE: return ")";
                case pattern::STRING: return "String";
                case pattern::LCOLCHETE: return "[";
                case pattern::RCOLCHETE: return "]";
                case pattern::CMDS: return "CMDS";
                case pattern::METODO: return "METODO";
                case pattern::TIPO: return "TIPO";
                case pattern::PARAMS: return "PARAMS";
                case pattern::DC: return "DC";
                case pattern::RETURN: return "return";
                case pattern::EXPRESSAO: return "EXPRESSAO";
                case pattern::PONTO_VIRGULA: return ";";
                case pattern::VIRGULA: return ",";
                case pattern::SUBTRACAO: return "-";
                case pattern::ADICAO: return "+";
                case pattern::DIVISAO: return "/";
                case pattern::MULTIPLICACAO: return "*";
                case pattern::NEGACAO: return "!";
                case pattern::ATRIBUICAO: return "=";
                case pattern::IGUAL: return "==";
                case pattern::DIFERENTE: return "!=";
                case pattern::MAIOR_IGUAL: return ">=";
                case pattern::MENOR_IGUAL: return "<=";
                case pattern::MAIOR: return ">";
                case pattern::MENOR: return "<";
                case pattern::NUM: return "Num";
                case pattern::DOUBLE: return "double";
                case pattern::MAIS_PARAMS: return "MAIS_PARAMS";
                case pattern::MAIS_VAR: return "MAIS_VAR";
                case pattern::VARS: return "VARS";
                case pattern::IF: return "if";
                case pattern::ELSE: return "else";
                case pattern::WHILE: return "while";
                case pattern::CONDICAO: return "CONDICAO";
                case pattern::PFALSA: return "PFALSA";
                case pattern::OUTPUT: return "System.out.println";
                case pattern::RESTO_IDENT: return "RESTO_IDENT";
                case pattern::LISTA_ARG: return "LISTA_ARG";
                case pattern::MAIS_IDENT: return "MAIS_IDENT";
                case pattern::ARGUMENTOS: return "ARGUMENTOS";
                case pattern::INPUT: return "lerDouble()";
                case pattern::VAR: return "VAR";
                case pattern::MAIS_DC: return "MAIS_DC";
                case pattern::CONDITIONAL_CMD: return "CONDITIONAL_CMD";
                case pattern::CMD: return "CMD";
                case pattern::RELACAO: return "RELACAO";
                case pattern::TERMO: return "TERMO";
                case pattern::OP_UN: return "OP_UN";
                case pattern::OP_AD: return "OP_AD";
                case pattern::OP_MUL: return "OP_MUL";
                case pattern::FATOR: return "FATOR";
                case pattern::MAIS_FATORES: return "MAIS_FATORES";
                case pattern::OUTROS_TERMOS: return "OUTROS_TERMOS";
                case pattern::EXP_IDENT: return "EXP_IDENT";
                case pattern::VAZIO: return "VAZIO";
                case pattern::END: return "$";
                default: return "ERROR";
            }
        }

        static std::string enumName(pattern p) {
            switch(p) {
                case pattern::OPERATOR: return "OPERATOR";
                case pattern::KEYWORD: return "KEYWORD";
                case pattern::PUNCTUATION: return "PUNCTUATION";
                case pattern::SIGNATURE: return "SIGNATURE";
                case pattern::PARAM: return "PARAM";

                case pattern::PROG: return "PROG";
                case pattern::INIT: return "INIT";
                case pattern::PUBLIC: return "PUBLIC";
                case pattern::CLASS: return "CLASS";
                case pattern::IDENTIFIER: return "IDENTIFIER";
                case pattern::LCHAVE: return "LCHAVE";
                case pattern::RCHAVE: return "RCHAVE";
                case pattern::STATIC: return "STATIC";
                case pattern::VOID: return "VOID";
                case pattern::MAIN: return "MAIN";
                case pattern::LPARENTESE: return "LPARENTESE";
                case pattern::RPARENTESE: return "RPARENTESE";
                case pattern::STRING: return "STRING";
                case pattern::LCOLCHETE: return "LCOLCHETE";
                case pattern::RCOLCHETE: return "RCOLCHETE";
                case pattern::CMDS: return "CMDS";
                case pattern::METODO: return "METODO";
                case pattern::TIPO: return "TIPO";
                case pattern::PARAMS: return "PARAMS";
                case pattern::DC: return "DC";
                case pattern::RETURN: return "RETURN";
                case pattern::EXPRESSAO: return "EXPRESSAO";
                case pattern::PONTO_VIRGULA: return "PONTO_VIRGULA";
                case pattern::VIRGULA: return "VIRGULA";
                case pattern::SUBTRACAO: return "SUBTRACAO";
                case pattern::ADICAO: return "ADICAO";
                case pattern::DIVISAO: return "DIVISAO";
                case pattern::MULTIPLICACAO: return "MULTIPLICACAO";
                case pattern::NEGACAO: return "NEGACAO";
                case pattern::ATRIBUICAO: return "ATRIBUICAO";
                case pattern::IGUAL: return "IGUAL";
                case pattern::DIFERENTE: return "DIFERENTE";
                case pattern::MAIOR_IGUAL: return "MAIOR_IGUAL";
                case pattern::MENOR_IGUAL: return "MENOR_IGUAL";
                case pattern::MAIOR: return "MAIOR";
                case pattern::MENOR: return "MENOR";
                case pattern::NUM: return "NUM";
                case pattern::DOUBLE: return "DOUBLE";
                case pattern::MAIS_PARAMS: return "MAIS_PARAMS";
                case pattern::MAIS_VAR: return "MAIS_VAR";
                case pattern::VARS: return "VARS";
                case pattern::IF: return "IF";
                case pattern::ELSE: return "ELSE";
                case pattern::WHILE: return "WHILE";
                case pattern::CONDICAO: return "CONDICAO";
                case pattern::PFALSA: return "PFALSA";
                case pattern::OUTPUT: return "OUTPUT";
                case pattern::RESTO_IDENT: return "RESTO_IDENT";
                case pattern::LISTA_ARG: return "LISTA_ARG";
                case pattern::MAIS_IDENT: return "MAIS_IDENT";
                case pattern::ARGUMENTOS: return "ARGUMENTOS";
                case pattern::INPUT: return "INPUT";
                case pattern::VAR: return "VAR";
                case pattern::MAIS_DC: return "MAIS_DC";
                case pattern::CONDITIONAL_CMD: return "CONDITIONAL_CMD";
                case pattern::CMD: return "CMD";
                case pattern::RELACAO: return "RELACAO";
                case pattern::TERMO: return "TERMO";
                case pattern::OP_UN: return "OP_UN";
                case pattern::OP_AD: return "OP_AD";
                case pattern::OP_MUL: return "OP_MUL";
                case pattern::FATOR: return "FATOR";
                case pattern::MAIS_FATORES: return "MAIS_FATORES";
                case pattern::OUTROS_TERMOS: return "OUTROS_TERMOS";
                case pattern::EXP_IDENT: return "EXP_IDENT";
                case pattern::VAZIO: return "VAZIO";
                case pattern::END: return "END";
                default: return "ERROR";
            }
        }

        static bool enumToBool(pattern p) {
            switch(p) {
                case pattern::SIGNATURE:
                case pattern::PARAM:

                case pattern::PROG:
                case pattern::INIT:
                case pattern::CMDS:
                case pattern::METODO:
                case pattern::TIPO:
                case pattern::PARAMS:
                case pattern::DC:
                case pattern::EXPRESSAO:
                case pattern::MAIS_PARAMS:
                case pattern::MAIS_VAR:
                case pattern::VARS:
                case pattern::CONDICAO:
                case pattern::PFALSA:
                case pattern::RESTO_IDENT:
                case pattern::LISTA_ARG:
                case pattern::MAIS_IDENT:
                case pattern::ARGUMENTOS:
                case pattern::VAR:
                case pattern::MAIS_DC:
                case pattern::CONDITIONAL_CMD:
                case pattern::CMD:
                case pattern::RELACAO:
                case pattern::TERMO:
                case pattern::OP_UN:
                case pattern::OP_AD:
                case pattern::OP_MUL:
                case pattern::FATOR:
                case pattern::MAIS_FATORES:
                case pattern::OUTROS_TERMOS:
                case pattern::EXP_IDENT:
                    return NON_TERMINAL;

                case pattern::OPERATOR:
                case pattern::KEYWORD:
                case pattern::PUNCTUATION:

                case pattern::INPUT:
                case pattern::OUTPUT:
                case pattern::PUBLIC:
                case pattern::CLASS:
                case pattern::IDENTIFIER:
                case pattern::LCHAVE:
                case pattern::RCHAVE:
                case pattern::STATIC:
                case pattern::VOID:
                case pattern::MAIN:
                case pattern::LPARENTESE:
                case pattern::RPARENTESE:
                case pattern::STRING:
                case pattern::LCOLCHETE:
                case pattern::RCOLCHETE:
                case pattern::IF:
                case pattern::ELSE:
                case pattern::WHILE:
                case pattern::PONTO_VIRGULA:
                case pattern::VIRGULA:
                case pattern::SUBTRACAO:
                case pattern::ADICAO:
                case pattern::DIVISAO:
                case pattern::MULTIPLICACAO:
                case pattern::NEGACAO:
                case pattern::ATRIBUICAO:
                case pattern::IGUAL:
                case pattern::DIFERENTE:
                case pattern::MAIOR_IGUAL:
                case pattern::MENOR_IGUAL:
                case pattern::MAIOR:
                case pattern::MENOR:
                case pattern::NUM:
                case pattern::DOUBLE:
                case pattern::RETURN:
                case pattern::VAZIO:
                default:
                    return TERMINAL;
            }
        }

        static pattern stringToEnum(const std::string & s) {
            if(s == "Operator") return pattern::OPERATOR;
            if(s == "Keyword") return pattern::KEYWORD;
            if(s == "Punctuation") return pattern::PUNCTUATION;

            if(s == "PROG") return pattern::PROG;
            if(s == "INIT") return pattern::INIT;
            if(s == "public") return pattern::PUBLIC;
            if(s == "class") return pattern::CLASS;
            if(s == "Identifier") return pattern::IDENTIFIER;
            if(s == "{") return pattern::LCHAVE;
            if(s == "}") return pattern::RCHAVE;
            if(s == "static") return pattern::STATIC;
            if(s == "void") return pattern::VOID;
            if(s == "main") return pattern::MAIN;
            if(s == "(") return pattern::LPARENTESE;
            if(s == ")") return pattern::RPARENTESE;
            if(s == "String") return pattern::STRING;
            if(s == "[") return pattern::LCOLCHETE;
            if(s == "]") return pattern::RCOLCHETE;
            if(s == "CMDS") return pattern::CMDS;
            if(s == "METODO") return pattern::METODO;
            if(s == "TIPO") return pattern::TIPO;
            if(s == "PARAMS") return pattern::PARAMS;
            if(s == "DC") return pattern::DC;
            if(s == "return") return pattern::RETURN;
            if(s == "EXPRESSAO") return pattern::EXPRESSAO;
            if(s == ";") return pattern::PONTO_VIRGULA;
            if(s == ",") return pattern::VIRGULA;
            if(s == "-") return pattern::SUBTRACAO;
            if(s == "+") return pattern::ADICAO;
            if(s == "/") return pattern::DIVISAO;
            if(s == "*") return pattern::MULTIPLICACAO;
            if(s == "!") return pattern::NEGACAO;
            if(s == "=") return pattern::ATRIBUICAO;
            if(s == "==") return pattern::IGUAL;
            if(s == "!=") return pattern::DIFERENTE;
            if(s == ">=") return pattern::MAIOR_IGUAL;
            if(s == "<=") return pattern::MENOR_IGUAL;
            if(s == ">") return pattern::MAIOR;
            if(s == "<") return pattern::MENOR;
            if(s == "Num") return pattern::NUM;
            if(s == "double") return pattern::DOUBLE;
            if(s == "MAIS_PARAMS") return pattern::MAIS_PARAMS;
            if(s == "MAIS_VAR") return pattern::MAIS_VAR;
            if(s == "VARS") return pattern::VARS;
            if(s == "if") return pattern::IF;
            if(s == "else") return pattern::ELSE;
            if(s == "while") return pattern::WHILE;
            if(s == "CONDICAO") return pattern::CONDICAO;
            if(s == "PFALSA") return pattern::PFALSA;
            if(s == "System.out.println" || s == "Output") return pattern::OUTPUT;
            if(s == "RESTO_IDENT") return pattern::RESTO_IDENT;
            if(s == "LISTA_ARG") return pattern::LISTA_ARG;
            if(s == "MAIS_IDENT") return pattern::MAIS_IDENT;
            if(s == "ARGUMENTOS") return pattern::ARGUMENTOS;
            if(s == "lerDouble()" || s == "Input") return pattern::INPUT;
            if(s == "VAR") return pattern::VAR;
            if(s == "MAIS_DC") return pattern::MAIS_DC;
            if(s == "CONDITIONAL_CMD") return pattern::CONDITIONAL_CMD;
            if(s == "CMD") return pattern::CMD;
            if(s == "RELACAO") return pattern::RELACAO;
            if(s == "TERNO") return pattern::TERMO;
            if(s == "OP_UN") return pattern::OP_UN;
            if(s == "OP_AD") return pattern::OP_AD;
            if(s == "OP_MUL") return pattern::OP_MUL;
            if(s == "FATOR") return pattern::FATOR;
            if(s == "MAIS_FATORES") return pattern::MAIS_FATORES;
            if(s == "OUTROS_TERMOS") return pattern::OUTROS_TERMOS;
            if(s == "EXP_IDENT") return pattern::EXP_IDENT;
            if(s == "$" || s == "End") return pattern::END;
            if(s == "VAZIO") return pattern::VAZIO;
            return pattern::ERROR;
        }

    public:
        pattern pattern;

        Type(): pattern(pattern::VAZIO) {}
        explicit Type(const enum pattern type): pattern(type) {}
        explicit Type(const std::string& s): pattern(stringToEnum(s)) {}

        std::string asString() {
            return enumName(this->pattern);
        }

        bool status() {
            return enumToBool(this->pattern);
        }

        std::string asValue() {
            return asValue(this->pattern);
        }

        static std::string asString(const enum pattern p) {
            return enumName(p);
        }

        static std::string asValue(const enum pattern p) {
            return enumToString(p);
        }

        static bool status(const enum pattern p) {
            return enumToBool(p);
        }

        static Type factory(const enum pattern p) {
            return Type(p);
        }

        bool operator==(const Type & t) const {
            return this->pattern == t.pattern;
        }
    };

    class token {
    public:
        Type type;
        std::string value;
        unsigned linha = 0;

        token() = default;
        explicit token(Type t): type(t), value(t.asValue()) {}
        token(const Type t, std::string value, unsigned linha): type(t), value(std::move(value)), linha(linha) {}

        bool operator==(const token & token) const {
            return std::tie(this->type, this->value) == std::tie(token.type, token.value);
        }
    };

    inline void showTokens(std::vector<token> tokens) {
        for(auto & [k, v, l] : tokens) {
            std::cout << l << ": [" << k.asString() << ", " << v << "]" << std::endl;
        }
    }

    // Function Definitions



}

#endif
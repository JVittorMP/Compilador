#ifndef COMPILADORES_LEX_H
#define COMPILADORES_LEX_H

namespace lex {

    const bool TERMINAL = true;
    const bool NON_TERMINAL = false;

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
            if(s == "System.out.println") return pattern::OUTPUT;
            if(s == "RESTO_IDENT") return pattern::RESTO_IDENT;
            if(s == "LISTA_ARG") return pattern::LISTA_ARG;
            if(s == "MAIS_IDENT") return pattern::MAIS_IDENT;
            if(s == "ARGUMENTOS") return pattern::ARGUMENTOS;
            if(s == "lerDouble()") return pattern::INPUT;
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
            if(s == "$") return pattern::END;
            if(s == "VAZIO") return pattern::VAZIO;
            return pattern::ERROR;
        }

    public:
        pattern pattern;

        Type(): pattern(pattern::VAZIO) {}
        explicit Type(enum pattern type): pattern(type) {}
        explicit Type(std::string s): pattern(this->stringToEnum(s)) {}

        std::string asString() {
            return enumName(this->pattern);
        }

        bool status() {
            return enumToBool(this->pattern);
        }

        std::string asValue() {
            return asValue(this->pattern);
        }

        static std::string asString(enum pattern p) {
            return enumName(p);
        }

        static std::string asValue(enum pattern p) {
            return enumToString(p);
        }

        static bool status(enum pattern p) {
            return enumToBool(p);
        }

        static Type factory(enum Type::pattern p) {
            return Type(p);
        }

        bool operator==(const Type & t) const {
            return this->pattern == t.pattern;
        }
    };

    class lexema {
    public:
        unsigned type;
        std::string value;
        bool terminal;

        lexema() = default;
        lexema(unsigned type, std::string value, bool terminal):
            type(type), value(std::move(value)), terminal(terminal) {}

    };

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

    class token02 {
    public:
        Type type;
        std::string value;
        unsigned linha = 0;

        token02() = default;
        token02(lex::Type t): type(t), value(t.asValue()), linha(0) {}
        token02(lex::Type t, std::string value, unsigned linha): type(t), value(std::move(value)), linha(linha) {}

        bool operator==(const token02 & token) const {
            return std::tie(this->type, this->value) == std::tie(token.type, token.value);
        }
    };

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
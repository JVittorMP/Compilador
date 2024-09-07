#pragma once

#ifndef __FLEX_LEXER
#define __FLEX_LEXER

#include <FlexLexer.h>

#endif

#include <vector>

typedef int alpha_token_t;

#undef YY_DECL
#define YY_DECL int Scanner::alpha_yylex(std::vector<alpha_token_t> & tokens)

class Scanner : public yyFlexLexer {
    public:
        alpha_yylex(std::vector<alpha_token_t> & tokens);
};
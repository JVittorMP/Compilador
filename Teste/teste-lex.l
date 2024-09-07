%{

#define FLEX_LEXER
#include "scanner.h"

#define INT_CAST            1
#define MAIN_CAST           2
#define RETURN_CAST         3
#define CONSTANT_CAST       4
#define IDENTIFIER_CAST     5
#define ASSIGN_CAST         6
#define OPERATOR_CAST       7
#define SEMICOLON_CAST      8
#define LBRACKET_CAST       9
#define RBRACKET_CAST       10
#define LBRACE_CAST         11
#define RBRACE_CAST         12

%}

%option c++
%option noyywrap
%option yyclass="Scanner"

IDENTIFIER  [a-zA-Z_][a-zA-Z0-9_]*
CONSTANT    [1-9][0-9]*|0
OPERATOR    "+"|"-"|"*"|"/"|"%"|"<"|"<="|">"|">="|"=="|"!="|"&"|"|"|"^"

%%

"int"           { yyout << INT_CAST << ' ' << yytext << std::endl; tokens.push_back(INT_CAST); }
"main"          { yyout << MAIN_CAST << ' ' << yytext << std::endl; tokens.push_back(INT_CAST); }
"return"        { yyout << RETURN_CAST << ' ' << yytext << std::endl; tokens.push_back(INT_CAST); }

{IDENTIFIER}    { yyout << IDENTIFIER_CAST << ' ' << yytext << std::endl; }
{CONSTANT}      { yyout << CONSTANT_CAST << ' ' << yytext << std::endl; }
{OPERATOR}      { yyout << OPERATOR_CAST << ' ' << yytext << std::endl; }
"="             { yyout << ASSIGN_CAST << ' ' << yytext << std::endl; }
";"             { yyout << SEMICOLON_CAST << ' ' << yytext << std::endl; }
"("             { yyout << LBRACKET_CAST << ' ' << yytext << std::endl; }
")"             { yyout << RBRACKET_CAST << ' ' << yytext << std::endl; }
"{"             { yyout << LBRACE_CAST << ' ' << yytext << std::endl; }
"}"             { yyout << RBRACE_CAST << ' ' << yytext << std::endl; }

[ \t\n]         { /* ignore whitespaces */ }

%%
/* 

Compiladores II
João Vittor de Moura Padilha - 202111310018

*/

%option noyywrap

/* Declaration Area */
%{
    #include "lex.h"

    #undef YY_DECL
    #define YY_DECL int scan(std::deque<lex::token> & tokens)

    unsigned line = 1;
%}

Keyword        (\double|int|boolean|class|extends|public|static|void|main|String|System.out.println|length|true|false|this|new|null|while|if|else|return)
Identifier     [a-zA-Z][a-zA-Z0-9_]*
Num            ([0-9]+|[0-9]*\.[0-9]+)
Operator       <=|>=|==|!=|&&|"||"|[-+*=/\<>!]
Punctuation    [(\)|\(|\}|\{|\]|\[|\;|\.|\,)]
Whitespace     [ \t\r\f]+
Input          (lerDouble\(\))
 
/*** rules for inputs ***/
%%

{Keyword}		    { tokens.push_back({lex::Type("Keyword"), yytext, line}); }
{Input}             { tokens.push_back({"lex::Type(Input"), yytext, line}); }
{Identifier}		{ tokens.push_back({"lex::Type(Identifier"), yytext, line}); }
{Num}			    { tokens.push_back({"lex::Type(Num"), yytext, line}); }
{Operator}		    { tokens.push_back({"lex::Type(Operator"), yytext, line}); }
{Punctuation}		{ tokens.push_back({"lex::Type(Punctuation"), yytext, line}); }
{Whitespace}		{ /* Whitespace Ignored */ }
\n                  { line++;}
<<EOF>>             { tokens.push_back({lex::Type("End"), "$", line}); return 0;}
.			        { printf("[Invalid Input (Lexical Error) on Line %d, %s]\n", line, yytext);}

%%
 
/*** User code section***/



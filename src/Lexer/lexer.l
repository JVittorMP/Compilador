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

{Keyword}		    { tokens.push_back({lex::type("Keyword"), yytext, line}); }
{Input}             { tokens.push_back({lex::type("Input"), yytext, line}); }
{Identifier}		{ tokens.push_back({lex::type("Identifier"), yytext, line}); }
{Num}			    { tokens.push_back({lex::type("Num"), yytext, line}); }
{Operator}		    { tokens.push_back({lex::type("Operator"), yytext, line}); }
{Punctuation}		{ tokens.push_back({lex::type("Punctuation"), yytext, line}); }
{Whitespace}		{ /* Whitespace Ignored */ }
\n                  { line++;}
<<EOF>>             { tokens.push_back({lex::Type("End"), "$", line}); return 0;}
.			        { tokens.push_back({lex::Type("ERROR"), "Invalid Input on Line: " + std::to_string(line) + " " + yytext, line}); } { printf("[Invalid Input (Lexical Error) on Line %d, %s]\n", line, yytext);}

%%
 
/*** User code section***/



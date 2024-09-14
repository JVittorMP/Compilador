#include <iostream>
#include <vector>
#include <string>

#include "Lexer/lexer.cpp"
#include "Lexer/lex.h"
#include "Parser/parser.cpp"
#include "Parser/AST/ast.h"
#include "Semantizer/semantizer.cpp"
//#include "Parser/AST/abstractSyntaxTree.cpp"
#include "CodeGenerator/generator.cpp"

// Sem Ponteiros
//#include "Parser/AST/novo/parseT.cpp"
//#include "Parser/AST/novo/ast.cpp"

// TesteNew
#include "Parser/neoParser.cpp"
#include "Parser/ast.cpp"
#include "CodeGenerator/generator02.cpp"

int main() {
    //std::string inputFile = "../Documentos/mini-java-exemplo.java";
    std::string inputFile = "../Documentos/input/input-04.txt";

    std::vector<lex::token> tokens = lex::scan(inputFile);

    for(auto & [k, v, l] : tokens) {
        std::cout << l << ": [" << k << ", " << v << "]" << std::endl;
    }

    auto it = tokens.begin();

    std::deque<lex::token02> tokens02;
    for(const auto& tk : tokens) {
        lex::Type t;
        if( tk.type == "Identifier" || tk.type == "Num" ||
            tk.type == "Keyword" || tk.type == "Punctuation" || tk.type == "Operator") {
            t = lex::Type(tk.type);
        } else {
            t = lex::Type(tk.value);
        }

        tokens02.emplace_back(t, tk.value, tk.linha);
        auto tm = tokens02.back();
    }

    auto it02 = tokens02.begin();
    ast::Node02* root = parse(it02);
    //exploreNode02(root);
    ast::Node02* ast = buildAST(root);
    explore02(ast);
    generate(ast);

    return 0;

//    if(sin::parse(it)) {
//        std::cout << "Parser: Tudo Certo!" <<  std::endl << std::endl;
//    } else {
//        std::cout << "Parser: Tudo Errado! Fim dos Tempos!" <<  std::endl;
//        return 0;
//    }

/*
    auto begin = tokens.begin();
    ast::Node* ast = buildAST(begin);
    explore02(ast);
    std::cout << std::endl << std::endl;
    if(analyse(ast)) {
        std::cout << "Semantic Analysis: Tudo certo!" << std::endl;
    } else {
        std::cout << "Semantic Analysis: Falha no analisador semantico!" << std::endl;
    }

    generate(ast);

    return 0;

    */
}

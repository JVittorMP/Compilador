#include <iostream>
#include <vector>
#include <string>

#include "Lexer/lexer.cpp"
#include "Lexer/lex.h"
#include "Parser/parser.cpp"
#include "Parser/AST/ast.h"
#include "Semantizer/semantizer.cpp"
//#include "Parser/AST/parseTree.cpp"
#include "Parser/AST/abstractSyntaxTree.cpp"

//#include "Parser/AST/save.cpp"

// Sem Ponteiros
//#include "Parser/AST/novo/parseT.cpp"
//#include "Parser/AST/novo/ast.cpp"

int main() {
    //std::string inputFile = "../Documentos/mini-java-exemplo.java";
    std::string inputFile = "../Documentos/input/input-02.txt";

    std::vector<lex::token> tokens = lex::scan(inputFile);

    for(auto & [k, v, l] : tokens) {
        std::cout << l << ": [" << k << ", " << v << "]" << std::endl;
    }

    auto it = tokens.begin();
    if(sin::parse(it)) {
        std::cout << "Tudo Certo!" <<  std::endl << std::endl;
    } else {
        std::cout << "Tudo Errado! Fim dos Tempos!" <<  std::endl;
        return 0;
    }

    auto begin = tokens.begin();
    ast::Node* ast = buildAST(begin);
    explore02(ast);
    std::cout << std::endl << std::endl;
    if(analyse(ast)) {
        std::cout << "Tudo certo!" << std::endl;
    } else {
        std::cout << "Falha no analisador semantico!" << std::endl;
    }

//    ast::Node* ast = ast::buildParseTree(begin);
//
//    //ast::Node ast = buildAST2(begin);
//
//    // Double Pointer Try
//    //ast::Node** nd = &ast;
//    //compress(nd);
//    //explore02(nd);
//
//    // Normal try
//    compress(ast);
//    explore02(ast);

    return 0;
}

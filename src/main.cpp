#include <iostream>
#include <vector>
#include <string>

#include "Lexer/lex.h"
#include "Parser/AST/ast.h"

#include "Lexer/lexer.cpp"
#include "Parser/parser.cpp"
#include "Parser/AST/ast.cpp"
#include "CodeGenerator/generator.cpp"

int main() {
    //const std::string inputFile = "../Documentos/mini-java-exemplo.java";
    const std::string inputFile = "../Documentos/input/input-03.txt";

    std::deque<lex::token> tokens = lex::scan(inputFile);

    for(auto & [k, v, l] : tokens) {
        std::cout << l << ": [" << k.asString() << ", " << v << "]" << std::endl;
    }

    // std::deque<lex::token> tokens02;
    // for(const auto& tk : tokens) {
    //     lex::Type t;
    //     if( tk.type == "Identifier" || tk.type == "Num" ||
    //         tk.type == "Keyword" || tk.type == "Punctuation" || tk.type == "Operator") {
    //         t = lex::Type(tk.type);
    //     } else {
    //         t = lex::Type(tk.value);
    //     }
    //
    //     tokens02.emplace_back(t, tk.value, tk.linha);
    //     auto tm = tokens02.back();
    // }

    auto it = tokens.begin();
    ast::Node* root = parse(it);
    ast::Node* ast = buildAST(root);
    explore02(ast);
    std::cout << std::endl;
    generate(ast);

    return 0;
}

#include "basic.h"

#include "Lexer/lex.h"
#include "Parser/AST/ast.h"

#include "Lexer/lexer.cpp"
#include "Parser/parser.cpp"
#include "Parser/AST/ast.cpp"
#include "CodeGenerator/generator.cpp"

int main() {
    //const std::string inputFile = "../Documentos/mini-java-exemplo.java";
    const std::string inputFile = "../Documentos/input/input-04.txt";

    std::deque<lex::token> tokens = lex::scan(inputFile);

    for(auto & [k, v, l] : tokens) {
        std::cout << l << ": [" << k.asString() << ", " << v << "]" << std::endl;
    }

    auto it = tokens.begin();
    ast::Node* root = parse(it);
    ast::Node* ast = buildAST(root);
    explore02(ast);
    std::cout << std::endl;
    generate(ast);

    return 0;
}

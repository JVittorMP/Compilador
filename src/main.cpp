#include "Lexer/lexer.cpp"
#include "Parser/parser.cpp"
#include "Parser/AST/ast.cpp"
#include "Semantizer/semantizer.cpp"
#include "CodeGenerator/generator.cpp"

int main() {
    //const std::string inputFile = "../Documentos/mini-java-exemplo.java";
    const std::string inputFile = "../Documentos/input/input-05.txt";

    const std::deque<lex::token> tokens = lex::scan(inputFile);
    sin::cursor cursor(tokens);
    ast::Node* root = sin::parse(cursor);
    ast::Node* ast = buildAST(root);

    if(analyse(ast)) {
        std::cout << "Semantic Analysis: Tudo certo!" << std::endl;
    } else {
        std::cout << "Semantic Analysis: Falha no analisador semantico!" << std::endl;
    }

    generate(ast);

    return 0;
}

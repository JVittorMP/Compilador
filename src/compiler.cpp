#include "def.h"
#include "Lexer/lexer.cpp"
#include "Parser/parser.cpp"
#include "Parser/AST/ast.cpp"
#include "Semantizer/semantizer.cpp"
#include "Generator/generator.cpp"

int main() {
    const std::string inputFile = "../Documentos/input/mini-java-exemplo.java";

    try {
        const std::deque<lex::token> tokens = lex::scan(inputFile);
        sin::cursor cursor(tokens);
        ast::Node* root = sin::parse(cursor);
        ast::Node* ast = ast::filter(root);
        sem::analyse(ast);
        cmd::generate(ast);
    } catch(compiler::Exception & e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

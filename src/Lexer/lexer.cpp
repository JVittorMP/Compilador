#include "lex.yy.c"

/**
 * @def
 * Procedimento incubido da tarefa de chamar o módulo
 * contendo o analisador léxico, gerando uma lista
 * de tokens representando as entradas do cpodigo fonte.
 *
 */
std::deque<lex::token> lex::scan(const std::string &input) {
    yyin = fopen(input.data(), "r");

    if(!yyin) {
        throw compiler::Exception(compiler::Exception::type::RUNTIME, std::format("File '{}' Not Found", input));
    }

    std::deque<lex::token> tokens;
    ::scan(tokens);
    for(const auto& tk : tokens) {
        if(tk.type.pattern != Type::pattern::ERROR) continue;
        throw compiler::Exception(compiler::Exception::type::LEXICAL, tk.value);
    }
    std::cout << "Lexical Analysis Concluded!" << std::endl;
    return tokens;
}
#include "lex.yy.c"

/**
 * @def
 * Procedimento incubido da tarefa de chamar o módulo
 * contendo o analisador léxico, gerando uma lista
 * de tokens representando as entradas do código fonte.
 */
std::deque<lex::token> lex::scan(const std::string &input) {
    yyin = fopen(input.data(), "r");

    if(!yyin) {
        throw compiler::Exception(compiler::Exception::model::RUNTIME, std::format("File '{}' Not Found", input));
    }

    std::deque<lex::token> tokens;
    ::scan(tokens);
    for(const auto& tk : tokens) {
        if(tk.pattern != lex::pattern::ERROR) continue;
        throw compiler::Exception(compiler::Exception::model::LEXICAL, tk.value);
    }
    std::cout << "Lexical Analysis Concluded!" << std::endl;
    return tokens;
}
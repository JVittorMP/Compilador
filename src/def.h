#ifndef COMPILADOR_DEF_H
#define COMPILADOR_DEF_H

#include "Lexer/lex.h"
#include "Parser/sin.h"
#include "Parser/AST/ast.h"
#include "Semantizer/sem.h"
#include "Generator/cmd.h"
#include "Interpreter/interpreter.h"

namespace lex {
    std::deque<lex::token> scan(const std::string & input);
}

namespace sin {
    int PROG(ast::Node* node, cursor & cursor);
    int INIT(ast::Node* node, cursor & cursor);
    int METODO(ast::Node* node, cursor & cursor);
    int PARAMS(ast::Node* node, cursor & cursor);
    int MAIS_PARAMS(ast::Node* node, cursor & cursor);
    int DC(ast::Node* node, cursor & cursor);
    int VAR(ast::Node* node, cursor & cursor);
    int VARS(ast::Node* node, cursor & cursor);
    int MAIS_VAR(ast::Node* node, cursor & cursor);
    int TIPO(ast::Node* node, cursor & cursor);
    int CMDS(ast::Node* node, cursor & cursor);
    int CONDITIONAL_CMD(ast::Node* node, cursor & cursor);
    int CMD(ast::Node* node, cursor & cursor);
    int PFALSA(ast::Node* node, cursor & cursor);
    int RESTO_IDENT(ast::Node* node, cursor & cursor);
    int LISTA_ARG(ast::Node* node, cursor & cursor);
    int ARGUMENTOS(ast::Node* node, cursor & cursor);
    int MAIS_IDENT(ast::Node* node, cursor & cursor);
    int EXP_IDENT(ast::Node* node, cursor & cursor);
    int CONDICAO(ast::Node* node, cursor & cursor);
    int RELACAO(ast::Node* node, cursor & cursor);
    int EXPRESSAO(ast::Node* node, cursor & cursor);
    int TERMO(ast::Node* node, cursor & cursor);
    int OP_UN(ast::Node* node, cursor & cursor);
    int FATOR(ast::Node* node, cursor & cursor);
    int OUTROS_TERMOS(ast::Node* node, cursor & cursor);
    int OP_AD(ast::Node* node, cursor & cursor);
    int MAIS_FATORES(ast::Node* node, cursor & cursor);
    int OP_MUL(ast::Node* node, cursor & cursor);

    int findNonTerminal(enum lex::pattern p, ast::Node* node, sin::cursor & cursor);
    int validateProduction(ast::Node* node, sin::cursor & cursor, std::deque<lex::token> & lexemas);
}

namespace ast {
    void eraseEmptyProductions(ast::Node* & node);
    void simplifyExpression(const ast::Node* node, std::deque<ast::Node*> & exp);
    void getVars(std::deque<ast::Node*> & v, const ast::Node* cur);
    void getDeclarations(std::deque<ast::Node*> & dc, const ast::Node* cur);
    void getCmds(std::deque<ast::Node*> & cmds, const ast::Node* cur);
    void evaluateNegNum(ast::Node* & cur);
    void orderAtribution(ast::Node* & node);
    void orderConditionals(ast::Node* & node);
    void orderOutput(ast::Node* & node);
    void getArguments(ast::Node* & node, std::deque<ast::Node*> & v);
    void filterCmds(ast::Node* & node);
    void getParams(std::deque<ast::Node*> & v, ast::Node* cur);
    void compressSignature(ast::Node* & node);
    void compressReturn(ast::Node* & node);
    void getMethod(ast::Node* node, std::deque<ast::Node*> & v);
    void compressStructure(ast::Node* & node);
    void removeInit(ast::Node* & root);
    void compress(ast::Node* & node);
    ast::Node* changeExpressionNode(ast::Node* ex);
    ast::Node* orderArguments(ast::Node* & node);
    ast::Node* filter(ast::Node* & root);
}

namespace sem {
    void avaluateExpressionIdentifierContext(const ast::Node* node, sem::scopeController & scope);
    void avaluateCommands(ast::Node* node, sem::scopeController & scope);
    void computeDeclarations(const ast::Node* node, sem::scopeController & scope);
    void computeParams(ast::Node* node, sem::scopeController & scope);
    void analyseMain(ast::Node* node, sem::scopeController & scope);
    void analyseMethod(ast::Node* node, sem::scopeController & scope);
    void semanticAnalysis(const ast::Node* root);
    void analyse(const ast::Node* root);
}

namespace cmd {
    std::string getComparisonCmd(const std::string& s);
    std::string getOperatorCmd(const std::string& s);
    void generateExpression(ast::Node* node, sem::scopeController & scope, cmd::Code & code);
    void generateCondition(ast::Node* node, sem::scopeController & scope, cmd::Code & code);
    void generateCommands(ast::Node* node, sem::scopeController & scope, cmd::Code & code);
    bool generateDeclarations(const ast::Node* node, sem::scopeController & scope, cmd::Code & code);
    bool generateSignature(const ast::Node* node, sem::scopeController & scope, cmd::Code & code);
    bool generateReturn(const ast::Node* node, sem::scopeController & scope, cmd::Code & code);
    void generateMain(ast::Node* node, sem::scopeController & scope, cmd::Code & code);
    void generateMethod(ast::Node* node, sem::scopeController & scope, cmd::Code & code);
    bool generate(const ast::Node* root);
}

namespace exec {
    void interpret(exec::Interpreter & interpreter);
}

#endif

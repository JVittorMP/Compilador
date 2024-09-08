#include "../basic.h"
#include "../Parser/AST/ast.h"
#include "../Semantizer/sem.h"

#include "./cmd.h"

std::string getComparisonCmd(const std::string& s) {

    /*
     *
     * → CPME : Comparação de Menor
     * → CPMA : Comparação de Maior
     * → CPIG : Comparação de Igualdade
     * → CDES : Comparação de Desigualdade
     * → CPMI : Comparação de Menor-Igual
     * → CMAI : Comparação de Maior-Igual
     *
     */

    if(s == "<") return "CPME";
    if(s == ">") return "CPMA";
    if(s == "!=") return "CDES";
    if(s == "==") return "CPIG";
    if(s == "<=") return "CPMI";
    if(s == ">=") return "CMAI";
    return "ERROR";
}

std::string getOperatorCmd(const std::string& s) {
    if(s == "+") return "SOMA";
    if(s == "-") return "SUBT";
    if(s == "*") return "MULT";
    if(s == "/") return "DIVI";
    return "ERROR";
}

void getExpression(ast::Node *node, sem::scopeController & scope, std::ofstream & code) {
    if(node->type == "Num") {
        code << cmd::Cmd("CRCT", {node->value}) << std::endl;
        return;
    }
    if(node->type == "Identifier") {
        code << cmd::Cmd("CRVL", {node->value}) << std::endl;
        return;
    }
    getExpression(node->tokens[1], scope, code);
    getExpression(node->tokens[0], scope, code);
    code << cmd::Cmd(getOperatorCmd(node->value)) << std::endl;
}

void getCondition(ast::Node *node, sem::scopeController & scope, std::ofstream & code) {
    getExpression(node->tokens[0]->tokens[0], scope, code);
    getExpression(node->tokens[2]->tokens[0], scope, code);
    code << cmd::Cmd(getComparisonCmd(node->tokens[1]->tokens[0]->value)) << std::endl;
    code << cmd::Cmd("DSVF") << std::endl;
}

// → LEIT : Lê um dado de entrada para o topo da pilha
// → ELIN : Indica Inicio de ELSE
// → ELND : Indica Fim de ELSE
// → DSVX : Indica Fim de IF/WHILE
void generateCommands(ast::Node *node, sem::scopeController & scope, std::ofstream & code) {
    for(auto nd : node->tokens) {
        auto cur = nd->tokens[0];
        if(cur->value == "System.out.println") {
            getExpression(nd->tokens[1]->tokens[0], scope, code);
            code << cmd::Cmd("IMPR") << std::endl;
        } else if(cur->value == "=") {
            if(cur->tokens[1]->type == "Input") {
                code << cmd::Cmd("LEIT") << std::endl;
            } else {
                getExpression(cur->tokens[1]->tokens[0], scope, code);
            }
            code << cmd::Cmd("ARMZ", {cur->tokens[0]->value}) << std::endl;
        } else if(cur->value == "if") {
            auto cond = nd->tokens[1];
            auto cmds = nd->tokens[2];
            getCondition(cond, scope, code);
            generateCommands(cmds, scope, code);
            if(nd->tokens.size() > 3) {
                code << cmd::Cmd("ELIN") << std::endl;
                generateCommands(nd->tokens[3]->tokens[1], scope, code);
                code << cmd::Cmd("ELND") << std::endl;
            } else {
                code << cmd::Cmd("DSVX") << std::endl;
            }
        } else if(cur->value == "while") {
            auto cond = nd->tokens[1];
            auto cmds = nd->tokens[2];
            getCondition(cond, scope, code);
            generateCommands(cmds, scope, code);
            if(nd->tokens.size() > 3) {
                code << cmd::Cmd("ELIN") << std::endl;
                generateCommands(nd->tokens[3]->tokens[1], scope, code);
                code << cmd::Cmd("ELND") << std::endl;
            } else {
                code << cmd::Cmd("DSVX") << std::endl;
            }
            // Indicar endereço do início do while
            code << cmd::Cmd("DSVI", {"ENDEREÇO PARA VOLTAR"}) << std::endl;
        } else if(cur->type == "Identifier") {
            code << cmd::Cmd("PUSHER", {"ENDERECO PARA RETORNAR APOS FIM DO PROCEDIMENTO"}) << std::endl;
            for(auto id : nd->tokens[1]->tokens) {
                code << cmd::Cmd("PARAM ", {id->value}) << std::endl;
            }
            code << cmd::Cmd("CHPR", {"ENDERECO DO PROCEDIMENTO"}) << std::endl;
        }
    }
}

bool generateDeclarations(const ast::Node* node, sem::scopeController & scope, std::ofstream & code) {
    for(const auto nd : node->tokens) {
        for(const auto id : nd->tokens[1]->tokens) {
            scope.declare(id->value);
            code << cmd::Cmd("ALME", {id->value}) << std::endl;
        }
    }
    return true;
}

bool generateSignature(const ast::Node* node, sem::scopeController & scope, std::ofstream & code) {
    // Caso não haja parâmetros
    if(node->tokens.size() < 3) return true;
    for(const auto nd : node->tokens[2]->tokens) {
        const auto id = nd->tokens[1];
        scope.declare(id->value);
        code << cmd::Cmd("ALME", {id->value}) << std::endl;
    }
    return true;
}

bool generateReturn(const ast::Node* node, sem::scopeController & scope, std::ofstream & code) {
    getExpression(node->tokens[1]->tokens[0], scope, code);
    code << cmd::Cmd("RTPR") << std::endl;
    return true;
}

void generateMain(ast::Node *node, sem::scopeController & scope, std::ofstream & code) {
    scope.initializeScope("main");
    for(auto nd : node->tokens) {
        if(nd->type == "DC") generateDeclarations(nd, scope, code);
        if(nd->type == "CMDS") generateCommands(nd, scope, code);
    }
}

// -> Proc, chamada de procedimento
void generateMethod(ast::Node *node, sem::scopeController & scope, std::ofstream & code) {
    scope.initializeScope(node->tokens[0]->tokens[0]->value);
    code << cmd::Cmd("PROC", {node->tokens[0]->tokens[0]->value}) << std::endl;
    for(const auto nd : node->tokens) {
        if(nd->type == "SIGNATURE") generateSignature(nd, scope, code);
        if(nd->type == "DC") generateDeclarations(nd, scope, code);
        if(nd->type == "CMDS") generateCommands(nd, scope, code);
        if(nd->type == "RETURN") generateReturn(nd, scope, code);
    }
}

/*
 *
 * Gerar primeiro os procedimentos para saber onde está armazenado os dados,
 * então, quando houver a chamada, sabemos onde voltar
 *
 */

bool generate(ast::Node* root) {
    sem::scopeController scope;

    std::ofstream code("../Documentos/code/code.txt");

    if(!code) {
        std::cout << "Error in creating file!!!";
        return false;
    } else {
        std::cout << "Success in creating file!!!";
    }

    // Analisa se existe declaração de método
    if(root->tokens.size() > 2) {
        auto signature = root->tokens[2]->tokens[0];
        auto method = signature->tokens[0]->value;
        /*
         * True: Há parâmetros no método
         * False: Não há parâmetros
         */
        if(signature->tokens.size() > 2) {
            scope.saveSignature(method, signature->tokens[2]->tokens.size());
        } else {
            scope.saveSignature(method);
        }
    }

    code << cmd::Cmd("INPP") << std::endl;
    for(auto nd : root->tokens) {
        if(nd->type == "INIT") {
            generateMain(nd, scope, code);
            code << cmd::Cmd("PARA") << std::endl;
        } else if(nd->type == "METODO") {
            generateMethod(nd, scope, code);
        }
    }
    code.close();
    return true;
}
#include "sem.h"

bool avaluateExpressionIdentifierContext(ast::Node* node, sem::scopeController & scope) {
    for(auto nd : node->tokens) {
        if(nd->type == "Identifier") {
            if(!scope.isValid(nd->value)) {
                std::cout << "Variavel [" + nd->value + "] nao declarada!" << std::endl;
                return false;
            }
        }
        avaluateExpressionIdentifierContext(nd, scope);
    }
    return true;
}

bool avaluateCommands(ast::Node* node, sem::scopeController & scope) {
    for(auto nd : node->tokens) {
        auto cur = nd->tokens[0];
        if(cur->value == "System.out.println") {
            if(!avaluateExpressionIdentifierContext(nd->tokens[1], scope)) return false;
        } else if(cur->value == "=") {
            if(!scope.isValid(cur->tokens[0]->value)) {
                std::cout << "Variavel [" + cur->tokens[0]->value + "] nao declarada!" << std::endl;
                return false;
            }
            if(cur->tokens[1]->type == "Input") continue;
            if(!avaluateExpressionIdentifierContext(cur->tokens[1], scope)) return false;
        } else if(cur->value == "if" || cur->value == "while") {
            if(!avaluateExpressionIdentifierContext(nd->tokens[1], scope)) return false;
            avaluateCommands(nd->tokens[2], scope);
            if(nd->tokens.size() > 3) avaluateCommands(nd->tokens[3]->tokens[1], scope); // Avalia Else
        } else if(cur->type == "Identifier") {
            std::string methodId = cur->value;
            if(!scope.isValidMethod(methodId)) {
                std::cout << "Metodo [" + methodId + "] inexistente!" << std::endl;
                return false;
            }
            unsigned args = nd->tokens[1]->tokens.size();
            unsigned params = scope.getMethodParamsSize(methodId);
            if(args != params) {
                std::cout << "Quantidade de argumentos passados ao metodo [" + methodId + "] incompativel!" << std::endl;
                std::cout << "Esperado [" << args << "] argumentos, [" << params << "] parametros recebidos!" << std::endl;
                return false;
            }
            if(!avaluateExpressionIdentifierContext(nd->tokens[1], scope)) return false;
        }
    }
    return true;
}

bool computeDeclarations(const ast::Node* node, sem::scopeController & scope) {
    for(const auto nd : node->tokens) {
        for(const auto id : nd->tokens[1]->tokens) {
            if(!scope.declare(id->value)) {
                std::cout << "Declaracao redundante do identificador [" << id->value << "]" << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool computeParams(ast::Node* node, sem::scopeController & scope) {
    for(auto nd : node->tokens) {
        if(nd->type == "PARAM") {
            // Deveria carregar os valores passados nos argumentos da função
            if(!scope.declare(nd->tokens[1]->value)) {
                /*
                 * Essa linha é improvável de acontecer, haja vista que contabilizamos um novo escopo e os
                 * parâmetros da função são as primeiras declarações do novo escopo
                 */
                std::cout << "Declaracao redundante do identificador [" << nd->tokens[1]->value << "]" << std::endl;
                return false;
            }
        }
        computeParams(nd, scope);
    }
    return true;
}

bool analyseMain(ast::Node* node, sem::scopeController & scope) {
    scope.initializeScope("main");
    for(auto nd : node->tokens) {
        if(nd->type == "DC") {
            if(!computeDeclarations(nd, scope)) return false;
        }
        if(nd->type == "CMDS") {
            if(!avaluateCommands(nd, scope)) return false;
        }
    }
    return true;
}

bool analyseMethod(ast::Node* node, sem::scopeController & scope) {
    scope.initializeScope(node->tokens[1]->tokens[1]->value);
    for(auto nd : node->tokens) {
        if(nd->type == "SIGNATURE") {
            if(nd->tokens.size() > 2) {
                if(!computeParams(nd->tokens[2], scope)) return false;
            }
        }
        if(nd->type == "RETURN") {
            if(!avaluateExpressionIdentifierContext(nd->tokens[1], scope)) return false;
        }
        if(nd->type == "DC") {
            if(!computeDeclarations(nd, scope)) return false;
        }
        if(nd->type == "CMDS") {
            if(!avaluateCommands(nd, scope)) return false;
        }
    }
    return true;
}

bool analyse(ast::Node* root) {
    sem::scopeController scope;

    // Armazena a declaração do método 'main'
    scope.saveSignature("main");

    // Analisa se existe declaração de método
    if(root->tokens.size() > 2) {
        auto signature = root->tokens[2]->tokens[0];
        /*
         * True: Há parâmetros no método
         * False: Não há parâmetros
         */
        if(signature->tokens.size() > 2) {
            scope.saveSignature(signature->tokens[0]->value, signature->tokens[2]->tokens.size());
        } else {
            scope.saveSignature(signature->tokens[0]->value);
        }
    }
    for(auto nd : root->tokens) {
        if(nd->type == "INIT") {
            if(!analyseMain(nd, scope)) return false;
        } else if(nd->type == "METODO") {
            if(!analyseMethod(nd, scope)) return false;
        }
    }
    return true;
}



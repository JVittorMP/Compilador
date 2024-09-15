#include "sem.h"
#include "../Parser/AST/ast.h"

bool avaluateExpressionIdentifierContext(const ast::Node* node, sem::scopeController & scope) {
    for(const auto nd : node->tokens) {
        if(nd->type.pattern == lex::Type::pattern::IDENTIFIER) {
            if(!scope.isValid(nd->value)) {
                const std::string msg = "On Line " + std::to_string(nd->line) + ": Variavel [" + nd->value + "] Ausente!";
                throw compiler::Exception(compiler::exception::SEMANTIC, msg);
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
                const std::string msg =  "On Line " + std::to_string(cur->tokens[0]->line) + ": Variavel [" + cur->tokens[0]->value + "] Ausente!";
                throw compiler::Exception(compiler::exception::SEMANTIC, msg);
            }
            if(cur->tokens[1]->type.pattern == lex::Type::pattern::INPUT) continue;
            if(!avaluateExpressionIdentifierContext(cur->tokens[1], scope)) return false;
        } else if(cur->value == "if" || cur->value == "while") {
            if(!avaluateExpressionIdentifierContext(nd->tokens[1], scope)) return false;
            avaluateCommands(nd->tokens[2], scope);
            if(nd->tokens.size() > 3) avaluateCommands(nd->tokens[3]->tokens[1], scope); // Avalia Else
        } else if(cur->type.pattern == lex::Type::pattern::IDENTIFIER) {
            std::string methodId = cur->value;
            if(!scope.isValidMethod(methodId)) {
                const std::string msg = "Metodo [" + methodId + "] Inexistente!";
                throw compiler::Exception(compiler::exception::SEMANTIC, msg);
            }
            unsigned args = nd->tokens[1]->tokens.size();
            unsigned params = scope.getMethodParamsSize(methodId);
            if(args != params) {
                const std::string msgPt1 = "Quantidade de argumentos passados ao metodo [" + methodId + "] incompativel!";
                const std::string msgPt2 = "\n\tEsperado [" + std::to_string(args) + "] argumentos, [" + std::to_string(params) + "] parametros recebidos!";
                throw compiler::Exception(compiler::exception::SEMANTIC, msgPt1 + msgPt2);
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
                const std::string msg = "On Line " + std::to_string(id->line) + ": Declaracao redundante do identificador [" + id->value + "]";
                throw compiler::Exception(compiler::exception::SEMANTIC, msg);
            }
        }
    }
    return true;
}

bool computeParams(ast::Node* node, sem::scopeController & scope) {
    for(auto nd : node->tokens) {
        if(nd->type.pattern == lex::Type::pattern::PARAM) {
            // Deveria carregar os valores passados nos argumentos da função
            if(!scope.declare(nd->tokens[1]->value)) {
                /*
                 * Essa linha é improvável de acontecer, haja vista que contabilizamos um novo escopo e os
                 * parâmetros da função são as primeiras declarações do novo escopo
                 */
                const std::string msg = "On Line " + std::to_string(nd->tokens[1]->line) + ": Declaracao redundante do identificador [" + nd->tokens[1]->value + "]";
                throw compiler::Exception(compiler::exception::SEMANTIC, msg);
            }
        }
        computeParams(nd, scope);
    }
    return true;
}

bool analyseMain(ast::Node* node, sem::scopeController & scope) {
    scope.initializeScope("main");
    for(auto nd : node->tokens) {
        if(nd->type.pattern == lex::Type::pattern::DC) {
            if(!computeDeclarations(nd, scope)) return false;
        }
        if(nd->type.pattern == lex::Type::pattern::CMDS) {
            if(!avaluateCommands(nd, scope)) return false;
        }
    }
    return true;
}

bool analyseMethod(ast::Node* node, sem::scopeController & scope) {
    scope.initializeScope(node->tokens[1]->tokens[1]->value);
    for(auto nd : node->tokens) {
        if(nd->type.pattern == lex::Type::pattern::SIGNATURE) {
            if(nd->tokens.size() > 2) {
                if(!computeParams(nd->tokens[2], scope)) return false;
            }
        }
        if(nd->type.pattern == lex::Type::pattern::RETURN) {
            if(!avaluateExpressionIdentifierContext(nd->tokens[1], scope)) return false;
        }
        if(nd->type.pattern == lex::Type::pattern::DC) {
            if(!computeDeclarations(nd, scope)) return false;
        }
        if(nd->type.pattern == lex::Type::pattern::CMDS) {
            if(!avaluateCommands(nd, scope)) return false;
        }
    }
    return true;
}

bool analyse(const ast::Node* root) {
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
        if(nd->type.pattern == lex::Type::pattern::INIT) {
            if(!analyseMain(nd, scope)) return false;
        } else if(nd->type.pattern == lex::Type::pattern::METODO) {
            if(!analyseMethod(nd, scope)) return false;
        }
    }
    return true;
}



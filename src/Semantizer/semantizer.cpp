#include "../def.h"

/**
 * @def
 * Busca recursivamente por identificadores presentes na árvore de expressões passada,
 * verificando se as referidas variáveis são válidas (pertencem ao escopo) e se foram
 * corretamente declaradas anteriormente.
 *
 * @param node
 * Nó raíz de uma subárvore que representa uma expressão aritmérica.
 */
void sem::avaluateExpressionIdentifierContext(const ast::Node* node, sem::scopeController & scope) {
    for(const auto nd : node->tokens) {
        if(nd->type.pattern == lex::pattern::IDENTIFIER) {
            if(scope.isValid(nd->value)) continue;
            const std::string msg = std::format("On Line {}: Declaracao da Variavel [{}] Inexistente!", nd->line, nd->value);
            throw compiler::Exception(compiler::Exception::type::SEMANTIC, msg);
        }
        avaluateExpressionIdentifierContext(nd, scope);
    }
}

/**
 * @def
 * Procedimento que percorre cada um dos comandos, identificando seu tipo e chamando
 * o procedimento adequado para tratar a respectiva subárvore.
 *
 * @param node
 * Nó raíz de uma subárvore que agrupa todos os comandos declarados em cada escopo.
 */
void sem::avaluateCommands(ast::Node* node, sem::scopeController & scope) {
    for(auto nd : node->tokens) {
        if(nd->type == lex::Type(lex::pattern::DC)) {
            computeDeclarations(nd, scope);
        } else {
            auto cur = nd->tokens.front();
            switch(cur->type.pattern) {
                case lex::pattern::KEYWORD: {
                    if(cur->value == lex::Type::asValue(lex::pattern::OUTPUT)) {
                        avaluateExpressionIdentifierContext(nd->tokens[1], scope);
                        break;
                    } else {
                        avaluateExpressionIdentifierContext(nd->tokens[1], scope);
                        scope.initializeInternScope();
                        avaluateCommands(nd->tokens[2], scope);
                        scope.endInternScope();
                        if(nd->tokens.size() > 3) {
                            scope.initializeInternScope();
                            avaluateCommands(nd->tokens[3]->tokens[1], scope);
                            scope.endInternScope();
                        }
                        break;
                    }
                }
                case lex::pattern::OPERATOR:
                case lex::pattern::ATRIBUICAO: {
                    const auto id = cur->tokens.front();
                    if (!scope.isValid(cur->tokens[0]->value)) {
                        const std::string msg = std::format("On Line {}: Declaracao da Variavel [{}] Inexistente!", id->line, id->value);;
                        throw compiler::Exception(compiler::Exception::type::SEMANTIC, msg);
                    }
                    if (cur->tokens[1]->type.pattern == lex::pattern::INPUT) break;
                    avaluateExpressionIdentifierContext(cur->tokens[1], scope);
                    break;
                }
                case lex::pattern::IDENTIFIER: {
                    std::string methodId = cur->value;
                    if (!scope.isValidMethod(methodId)) {
                        const std::string msg = std::format("Metodo [{}] Inexistente!", methodId);
                        throw compiler::Exception(compiler::Exception::type::SEMANTIC, msg);
                    }
                    unsigned args = nd->tokens[1]->tokens.size();
                    unsigned params = scope.getMethodParamsSize(methodId);
                    if (args != params) {
                        const std::string msgPt1 = std::format("Quantidade de argumentos passados ao metodo [{}] incompativel! {}", methodId, '\n');
                        const std::string msgPt2 = std::format("Esperado [{}] argumentos, [{}] parametros recebidos!", args, params);
                        throw compiler::Exception(compiler::Exception::type::SEMANTIC, msgPt1 + msgPt2);
                    }
                    avaluateExpressionIdentifierContext(nd->tokens[1], scope);
                    break;
                }
                default:
                    std::string msg = std::format("Estrutura [{}] Nao Identificada", cur->type.asString());
                    throw compiler::Exception(compiler::Exception::type::SEMANTIC, msg);
            }
        }
    }
}

/**
 * @def
 * Procedimento que avalia a validade dos identificadores declaradas para o respectivo
 * escopo, reconhecendo redundâncias na declaração de variáveis.
 *
 * @param node
 * Nó raíz de uma subárvore que representa a região de declaração de cada escopo.
 */
void sem::computeDeclarations(const ast::Node* node, sem::scopeController & scope) {
    for(const auto nd : node->tokens) {
        for(const auto id : nd->tokens[1]->tokens) {
            if(scope.declare(id->value)) continue;
            const std::string msg = std::format("On Line {}: Declaracao redundante do identificador [{}]", id->line, id->value);
            throw compiler::Exception(compiler::Exception::type::SEMANTIC, msg);
        }
    }
}

/**
 * @def
 * Avalia a validade dos parâmetros da assinatura de um método.
 *
 * @param node
 * Nó raíz de uma subárvore que representa os parâmetros contidos na assinatura de um método.
 */
void sem::computeParams(ast::Node* node, sem::scopeController & scope) {
    for(auto nd : node->tokens) {
        if(nd->type.pattern == lex::pattern::PARAM) {
            const auto param = nd->tokens[1];
            // Deveria carregar os valores passados nos argumentos da função
            if(!scope.declare(param->value)) {
                /*
                 * Essa linha é improvável de acontecer, haja vista que contabilizamos um novo escopo e os
                 * parâmetros da função são as primeiras declarações do novo escopo
                 */
                const std::string msg = std::format("On Line {}: Declaracao redundante do identificador [{}]", param->line, param->value);
                throw compiler::Exception(compiler::Exception::type::SEMANTIC, msg);
            }
        }
        computeParams(nd, scope);
    }
}

/**
 * @def
 * Avalia as duas subestruturas contidas na configuração de inicialização da classe.
 *
 * @param node
 * Nó raiz de uma subárvore que representa o procedimento inicial da classe.
 */
void sem::analyseMain(ast::Node* node, sem::scopeController & scope) {
    scope.initializeScope("main");
    for(auto nd : node->tokens) {
        switch(nd->type.pattern) {
            case lex::pattern::CMDS:
                avaluateCommands(nd, scope);
                break;
            default:
                std::string msg = std::format("Estrutura [{}] Nao Identificada", nd->type.asString());
                throw compiler::Exception(compiler::Exception::type::SEMANTIC, msg);
        }
    }
}

/**
 * @def
 * Avalia as duas subestruturas contidas no procedimento da classe.
 *
 * @param node
 * Nó raiz de uma subárvore que representa o método inicial da classe.
 */
void sem::analyseMethod(ast::Node* node, sem::scopeController & scope) {
    scope.initializeScope(node->tokens[0]->tokens[0]->value);
    for(auto nd : node->tokens) {
        switch(nd->type.pattern) {
            case lex::pattern::SIGNATURE:
                if(nd->tokens.size() > 2) computeParams(nd->tokens[2], scope);
                break;
            case lex::pattern::RETURN:
                avaluateExpressionIdentifierContext(nd->tokens[1], scope);
                break;
            case lex::pattern::CMDS:
                avaluateCommands(nd, scope);
                break;
            default:
                std::string msg = std::format("Estrutura [{}] Nao Identificada", nd->type.asString());
                throw compiler::Exception(compiler::Exception::type::SEMANTIC, msg);
        }
    }
}

/**
 * @def
 * Procedimento que verifica a estrutura dos procedimentos do código,
 * chamando as rotinas de tratamento adequadas para cada caso.
 *
 * @param root
 * Nó raíz da Árvore Sintática Abstrata representativa do programa.
 *
 * @Observações
 *      Root Size Condition - Analisa de existe declaração de método
 * <br> Signature Size Condition - Verifica se existe parâmetros
 */
void sem::semanticAnalysis(const ast::Node* root) {
    sem::scopeController scope;
    scope.saveSignature("main");

    if(root->tokens.size() > 2) {
        auto signature = root->tokens[2]->tokens[0];
        if(signature->tokens.size() > 2) {
            scope.saveSignature(signature->tokens[0]->value, signature->tokens[2]->tokens.size());
        } else {
            scope.saveSignature(signature->tokens[0]->value);
        }
    }
    for(auto nd : root->tokens) {
        if(nd->type.pattern == lex::pattern::INIT) {
            analyseMain(nd, scope);
        } else if(nd->type.pattern == lex::pattern::METODO) {
            analyseMethod(nd, scope);
        }
    }
}

void sem::analyse(const ast::Node* root) {
    semanticAnalysis(root);
    std::cout << "Semantic Analysis Concluded!" << std::endl;
}



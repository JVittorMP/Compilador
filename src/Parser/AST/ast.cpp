#include "expTree.cpp"

/**
 * @def
 * Procedimento que realiza tratamento sobre a região de declaração de variáveis
 * através de uma abordagem recursiva sobre a estrutura da árvore.
 *
 */
void ast::getVars(std::deque<ast::Node*> & v, const ast::Node* cur) {
    if(cur->tokens.empty()) return;
    for(auto n : cur->tokens) {
        if(n->pattern == lex::pattern::IDENTIFIER) v.push_back(n);
        getVars(v, n);
    }
}

/**
 * @def
 * Procedimento identifica o fluxo de tratamento de comandos de declaração.
 *
 * @param dc
 * Raíz de uma subárvore que represent ao bloco de declarações.
 */
void ast::getDeclarations(std::deque<ast::Node*> & dc, const ast::Node* cur) {
    if(cur->tokens.empty()) return;
    for(auto n : cur->tokens) {
        if(n->pattern != lex::pattern::VAR) {
            getDeclarations(dc, n);
            continue;
        }
        for(const auto b : n->tokens) {
            if(b->pattern != lex::pattern::VARS) continue;
            std::deque<ast::Node*> vars;
            getVars(vars, b);
            b->tokens = vars;
        }
        dc.push_back(n);
    }
}

/**
 * @def
 * Procedimento que define o fluxo de tratamento de cada tipo de comando
 * durante busca recursiva pela estrutura da árvore.
 */
void ast::getCmds(std::deque<ast::Node*> & cmds, const ast::Node* cur) {
    if(cur->tokens.empty()) return;
    for(auto & n : cur->tokens) {
        if(n->pattern == lex::pattern::CMD || n->pattern == lex::pattern::CONDITIONAL_CMD || n->pattern == lex::pattern::DC) {
            if(n->tokens[0]->value == lex::value(lex::pattern::OUTPUT)) {
                std::deque<ast::Node*> subs;
                for(auto nd : n->tokens) {
                    if(!lex::terminal(nd->pattern) || nd->value == lex::value(lex::pattern::OUTPUT)) subs.push_back(nd);
                }
                n->tokens = subs;
            }
            cmds.push_back(n);
        } else {
            getCmds(cmds, n);
        }
    }
}

/**
 * @def
 * percorre a estrutura da árvore sintática buscando operadores
 * unários de inversão e agrupando-os em um único nó com seus
 * respectivos operandos.
 *
 * @param cur
 * Raíz de uma árvore que representa uma expressão aritmética.
 */
void ast::evaluateNegNum(ast::Node* & cur) {
    if(cur->tokens.empty()) return;
    for(auto & nd : cur->tokens) {
        if(nd->pattern == lex::pattern::TERMO) {
            auto temp = nd->tokens[0];
            if(temp->pattern == lex::pattern::OP_UN) {
                nd->tokens[0] = ast::Node::pointer(lex::pattern::OP_UN, lex::value(lex::pattern::SUBTRACAO), temp->line);
            }
        }
        evaluateNegNum(nd);
    }
}

/**
 * @def
 * Transforma a estrutura sintática responsável por gerar uma expressão
 * aritmética da gramática de modo a estruturá-la conforme uma árvore
 * de expressões.
 *
 * @param ex
 * Raíz da estrutura de uma expressão obtida conforme a árvore sintática
 *
 * @return
 * Retorna um Nó que consiste na raíz de uma árvore de expressões
 */
ast::Node* ast::changeExpressionNode(ast::Node* ex) {
    std::deque<ast::Node*> v;
    evaluateNegNum(ex);
    ast::Node* exCpy = ex;
    simplifyExpression(exCpy, v);
    exCpy = exp::buildTree(v);
    ex->tokens.clear();
    ex->tokens.push_back(exCpy);
    return ex;
}

/**
 * @def
 * Ordena a estrutura de um comando de atribução.
 *
 * @param node
 * Raíz de uam árvore que representa um comando de atribuição.
 */
void ast::orderAtribution(ast::Node* & node) {
    ast::Node* & id = node->tokens[0];
    ast::Node* & ri = node->tokens[1];
    ast::Node* & op = ri->tokens[0];
    ast::Node* & ex = ri->tokens[1]->tokens[0];

    if(ex->pattern != lex::pattern::INPUT) ex = changeExpressionNode(ex);

    auto novo = ast::Node::pointer(op->pattern, op->value, op->line);
    novo->tokens.push_back(id);
    novo->tokens.push_back(ex);

    id = novo;
    node->tokens.pop_back(); // Retirar "REST_IDENT do final de Node(CMD)"
}

/**
 * @def
 * Percorre a estrutura de uma árvore de expressões, concatenando
 * os elementos de forma a ordená-los em formato de expressão infixa
 *
 * @param node
 * Raíz de uma subárvore representando uma expressão aritmética.
 */
void ast::simplifyExpression(const ast::Node* node, std::deque<ast::Node*> & exp) {
    for(auto nd : node->tokens) {
        auto p = nd->pattern;
        if(p == lex::pattern::NUM || p == lex::pattern::OPERATOR || p == lex::pattern::IDENTIFIER || p == lex::pattern::PUNCTUATION || p == lex::pattern::OP_UN) exp.push_back(nd);
        simplifyExpression(nd, exp);
    }
}

/**
 * @def
 * Ordena as estruturas internas de uma condição.
 *
 * @param node
 * Raíz de uma subárvore que representa a condição de um
 * comando de desvio de fluxo.
 */
void ast::orderConditionals(ast::Node* & node) {
    ast::Node* & cond = node->tokens[1];
    ast::Node* & ex1 = cond->tokens[0];
    ast::Node* & ex2 = cond->tokens[2];

    ex1 = changeExpressionNode(ex1);
    ex2 = changeExpressionNode(ex2);
}

/**
 * @def
 * Ordena as instruções internas de um comando de impressão no terminal
 *
 * @param node
 * Raíz de uma árvore que representa um comando de impressão no terminal
 */
void ast::orderOutput(ast::Node* & node) {
    std::deque<ast::Node*> exp;
    ast::Node* & ex = node->tokens[1];
    ex = changeExpressionNode(ex);
}

/**
 * @def
 * Procedimento que percorre a estrutura de argumentos de uma
 * chamada de procedimento e agrupa-os sob a mesma hierarquia.
 *
 * @param node
 * Raíz de uma subárvore que representa os argumentos de uma
 * chamada de procedimento.
 */
void ast::getArguments(ast::Node* & node, std::deque<ast::Node*> & v) {
    for(auto nd : node->tokens) {
        if(nd->pattern == lex::pattern::IDENTIFIER) v.push_back(nd);
        getArguments(nd, v);
    }
}

/**
 * @def
 * Define a rotina de comandos que reestrutura os argumentos de uma
 * chamada de procedimento.
 *
 * @param node
 * Raíz de uma subárvore que contém a estrutura dos argumentos de
 * uma chamada de procedimento.
 *
 * @return
 * O nó reestruturado para um formato mais adequaado.
 */
ast::Node* ast::orderArguments(ast::Node* & node) {
    std::deque<ast::Node*> v;
    getArguments(node, v);
    node->tokens = v;
    return node;
}

/**
 * @def
 * Rotina auxiliar responsável por filtrar uma região de comandos.
 *
 * @param node
 * Nó raíz de uma subárvore que agrupa uma sequência de comandos.
 */
void ast::filterCmds(ast::Node* & node) {
    for(auto & n : node->tokens) {
        auto cur = n->tokens.front();
        auto val = cur->value;
        if(cur->pattern == lex::pattern::KEYWORD) {
            if(val == lex::value(lex::pattern::OUTPUT)) orderOutput(n);
            if(val == lex::value(lex::pattern::IF) || val == lex::value(lex::pattern::WHILE)) orderConditionals(n);
        }
        else if(cur->pattern == lex::pattern::IDENTIFIER) {
            if(n->tokens[1]->tokens.front()->pattern == lex::pattern::OPERATOR) {
                orderAtribution(n);
            } else {
                if(!n->tokens[1]->tokens.empty()) n->tokens[1] = orderArguments(n->tokens[1]->tokens[0]->tokens[0]);
                else n->tokens.pop_back();
            }
        }
    }
}

/**
 * @def
 * Define a rotina de tratamento para a subárvore que contém os
 * parâmetros de um método.
 *
 * @param cur
 * Nó raíz da subárvore que representa os parâmetros
 */
void ast::getParams(std::deque<ast::Node*> & v, ast::Node* cur) {
    if(cur->tokens.empty()) return;
    auto last = cur->tokens.back();

    auto param = ast::Node::pointer(lex::pattern::PARAM);
    param->tokens.push_back(cur->tokens[0]);
    param->tokens.push_back(cur->tokens[1]);
    v.push_back(param);
    if(last->pattern == lex::pattern::MAIS_PARAMS) getParams(v, last->tokens.front());
}

/**
 * @def
 * Procedimento de aborda o tratamento da assinatura de um método.
 *
 * @param node
 * Nó raíz de uma subárvore que representa a assinatura de um método.
 */
void ast::compressSignature(ast::Node* & node) {
    std::deque<ast::Node*> v;
    ast::Node* & params = node->tokens[2];
    getParams(v, params);
    params->tokens = v;
}

/**
 * @def
 * Procedimento que designa o tratamento adequado à estrutura do
 * retorno de um método.
 *
 * @param node
 * Raíz de uma subárvore que contém o retorno de um procedimento.
 */
void ast::compressReturn(ast::Node* & node) {
    std::deque<ast::Node*> v;
    ast::Node* & exp = node->tokens[1];
    exp = changeExpressionNode(exp);
}

/**
 * @def
 * Define a rotina de tratamento de uma subárvore que representa um método.
 *
 * @param node
 * Nó raíz de uma subárvore que contém a estrutura de um método.
 */
void ast::getMethod(ast::Node* node, std::deque<ast::Node*> & v) {
    auto signature =  ast::Node::pointer(lex::pattern::SIGNATURE);
    auto retorno = ast::Node::pointer(lex::pattern::RETURN);
    for(auto & nd : node->tokens) {
        auto pattern = nd->pattern;
        if(pattern == lex::pattern::IDENTIFIER) signature->tokens.push_front(nd);
        if(pattern == lex::pattern::TIPO || pattern == lex::pattern::PARAMS) signature->tokens.push_back(nd);
        if(pattern == lex::pattern::DC || pattern == lex::pattern::CMDS) v.push_back(nd);
    }
    retorno->tokens.push_back(node->tokens.end()[-2]);
    retorno->tokens.push_back(node->tokens.back());
    if(signature->tokens.size() == 3) compressSignature(signature);
    compressReturn(retorno);
    node->tokens.clear();
    v.push_front(signature);
    v.push_back(retorno);
}

/**
 * @def
 * Procedimento responsável por comprimir as estruturas da contidas na árvore.
 */
void ast::compressStructure(ast::Node* & node) {
    if(node->tokens.empty()) return;
    std::deque<ast::Node*> v;

    if(node->pattern == lex::pattern::DC) {
        getDeclarations(v, node);
    }
    else if(node->pattern == lex::pattern::CMDS) {
        getCmds(v, node);
    }
    else if(node->pattern == lex::pattern::METODO) {
        getMethod(node, v);
    }

    node->tokens = v;
    if(node->pattern == lex::pattern::CMDS) filterCmds(node);
}

void eraseEmptyProductionsOnExpressionNode(ast::Node* & node) {
    for(int i = 0; i < size(node->tokens); i++) {
        ast::Node* n = node->tokens[i];
        if(n->tokens.empty()) continue;
        if(n->tokens[0]->pattern == lex::pattern::VAZIO) {
            node->tokens.erase(node->tokens.begin() + i--);
            continue;
        }
        eraseEmptyProductionsOnExpressionNode(n);
    }
}

/**
 * @def
 * Percorre a estrutura da árvore recursivamente, identificando
 * produções vazias e removendo-as da árvore sintática.
 *
 * @param node
 * Raíz da árvore sintática.
 */
void ast::eraseEmptyProductions(ast::Node* & node) {
    for(int i = 0; i < size(node->tokens); i++) {
        ast::Node* n = node->tokens[i];
        if(n->pattern == lex::pattern::EXPRESSAO) {
            eraseEmptyProductionsOnExpressionNode(n);
            continue;
        }
        if(n->pattern == lex::pattern::PUNCTUATION) {
            node->tokens.erase(node->tokens.begin() + i--);
            continue;
        }
        if(n->tokens.empty()) continue;
        if(n->tokens[0]->pattern == lex::pattern::VAZIO) {
            node->tokens.erase(node->tokens.begin() + i--);
            continue;
        }
        eraseEmptyProductions(n);
    }
}

/**
 * @def
 * Remove elementos desnecessários da estrutura de inicialização do programa
 *
 * @param root
 * Raíz da árvore sintárica.
 */
void ast::removeInit(ast::Node* & root) {
    const auto init = (*root)[1];

    auto itInit = init->tokens.begin();
    while(itInit != init->tokens.end()) {
        if((*itInit)->pattern != lex::pattern::KEYWORD) break;
        init->tokens.erase(itInit);
        ++itInit;
    }

    init->value = "public static void main";
}

/**
 * @def
 * Percorre a árvore sintática identificando os nós
 * significativos e inicializando suas respectivas rotinas
 * de compreesão.
 */
void ast::compress(ast::Node* & node) {
    for(auto & n : node->tokens) {
        if(n->tokens.empty()) continue;

        auto pattern = n->pattern;
        if(pattern == lex::pattern::DC || pattern == lex::pattern::CMDS || pattern == lex::pattern::METODO) {
            compressStructure(n);
        }
        compress(n);
    }
}

/**
 * @def
 * Filtra as entradas da Árvore Sintática Concreta, eliminando elementos desnecessários
 * para a construção de uma Árvore Sintática Abstrata capaz de representar o programa.
 *
 * @Observações
 * Pop Front Twice - Retira entradas Desnecessárias do Programa (public and class Keywords)
 *
 * @return
 * Retorna uma Árvore Sintática Abstrata que representa uma estrutura sufientemente
 * similar ao programa corrente analisado pelo compilador.
 */
ast::Node* ast::filter(ast::Node* & root) {
    eraseEmptyProductions(root);

    root->tokens.pop_front();
    root->tokens.pop_front();

    removeInit(root);
    compress(root);
    std::ofstream file("../Documentos/Code/ast.txt");
    sin::explore(file, root);
    return root;
}

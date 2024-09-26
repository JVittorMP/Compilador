#include "../def.h"

/**
 * @def
 * Retorna o tipo de instrução de acordo com o operador
 * relacional recebido como parâmetro.
 *
 * @Instruções
 *      CPME: Comparação Menor
 * <br> CPMA: Comparação Maior
 * <br> CPIG: Comparação Igualdade
 * <br> CDES: Comparação Desigualdade
 * <br> CPMI: Comparação Menor Inclusivo
 * <br> CMAI: Comparação Maior Inclusivo
 */
std::string cmd::getComparisonCmd(const std::string& s) {
    if(s == "<") return "CPME";
    if(s == ">") return "CPMA";
    if(s == "!=") return "CDES";
    if(s == "==") return "CPIG";
    if(s == "<=") return "CPMI";
    if(s == ">=") return "CMAI";
    return "ERROR";
}

/**
 * @def
 * Retorna o tipo de instrução de acordo com operador
 * aritmético recebido como parâmetro.
 *
 * @Instruções
 *      SOMA: Intrução Soma
 * <br> SUBT: Intrução Subtração
 * <br> MULT: Intrução Multiplicação
 * <br> DIVI: Intrução Divisão
 */
std::string cmd::getOperatorCmd(const std::string& s) {
    if(s == "+") return "SOMA";
    if(s == "-") return "SUBT";
    if(s == "*") return "MULT";
    if(s == "/") return "DIVI";
    return "ERROR";
}

/**
 * @def
 * Trata acerca da geração de código para as instruções que
 * envolvem expressões aritméticas. Esse procedimento também
 * é responsável por resolver árvores binárias de expressão
 * à maneira que estão estruturadas,
 *
 * @Instruções
 *      CRCT: Indica o carregamento de uma constante ao topo da pilha
 * <br> CRVL: Indica o carregamento de uma variável ao topo da pilha
 *
 * @Observações
 * Early Return Pattern - O método não possui parâmetros.
 */
void cmd::generateExpression(ast::Node* node, sem::scopeController & scope, cmd::Code & code) {
    if(node->type.pattern == lex::pattern::NUM) {
        auto crct = new cmd::Cmd("CRCT", {node->value});
        code.saveCommand(crct);
        return;
    }
    if(node->type.pattern == lex::pattern::IDENTIFIER) {
        auto crvl = new cmd::Cmd("CRVL", {node->value});
        code.saveCommand(crvl);
        return;
    }
    generateExpression(node->tokens[1], scope, code);
    generateExpression(node->tokens[0], scope, code);
    auto opr = new cmd::Cmd(getOperatorCmd(node->value));
    code.saveCommand(opr);
}

/**
 * @def
 * Trata acerca da geração de código para as condições de comandos
 * de desvio de fluxo.
 *
 * @Instruções
 * DSVF: Indica um desvio condicional para a instrução do argumento.
 */
void cmd::generateCondition(ast::Node* node, sem::scopeController & scope, cmd::Code & code) {
    generateExpression(node->tokens[0]->tokens[0], scope, code);
    generateExpression(node->tokens[2]->tokens[0], scope, code);
    auto comp = new cmd::Cmd(getComparisonCmd(node->tokens[1]->tokens[0]->value));
    code.saveCommand(comp);
    auto dsvf = new cmd::Cmd("DSVF");
    code.saveCommand(dsvf);
    code.initializeJump(dsvf);
}

/**
 * @def
 * Trata acerca da geração de código para as instruções de desvio
 * condicional, além de instruções como atribuição e impressão de
 * valores no terminal.
 *
 *
 * @Instruções
 *      IMPR: Indica a impressão de um dado na saída padrão (Terminal)
 * <br> LEIT: Indica a leitura de um dado da entrada padrão (Terminal)
 * <br> ARMZ: Armazena o dado do topo na pilha no endereço do argumento passado
 * <br> DSVI: Indica desvio incondicional para o endereço do argumento passado
 * <br> PSHR: Empilha o índice da instrução de retorno após finalização do procedimento
 * <br> PRMT: Armazena o valor do parâmetro no topo da pilha
 * <br> CHPR: Indica o desvio para o endereço do argumento passado
 *
 * @Observações
 * Early Return Pattern - O método não possui parâmetros.
 */
void cmd::generateCommands(ast::Node* node, sem::scopeController & scope, cmd::Code & code) {
    for(auto nd : node->tokens) {
        auto cur = nd->tokens[0];
        if(cur->value == "System.out.println") {
            generateExpression(nd->tokens[1]->tokens[0], scope, code);
            auto impr = new cmd::Cmd("IMPR");
            code.saveCommand(impr);
        } else if(cur->value == "=") {
            if(cur->tokens[1]->type.pattern == lex::pattern::INPUT) {
                auto leit = new cmd::Cmd("LEIT");
                code.saveCommand(leit);
            } else {
                generateExpression(cur->tokens[1]->tokens[0], scope, code);
            }
            auto armz = new cmd::Cmd("ARMZ", {cur->tokens[0]->value});
            code.saveCommand(armz);
        } else if(cur->value == "if") {
            // Para aumentar os passos dos elses para cada if
            code.ifsc += nd->tokens.size() > 3;
            auto cond = nd->tokens[1];
            auto cmds = nd->tokens[2];
            generateCondition(cond, scope, code);
            generateCommands(cmds, scope, code);

            // Não tem else
            if(nd->tokens.size() > 3) {
                code.ifsc--;
                auto dsvf = new cmd::Cmd("DSVI");
                code.saveCommand(dsvf);
                code.endJump();
                code.initializeJump(dsvf);
                generateCommands(nd->tokens[3]->tokens[1], scope, code);
                code.endJump();
            } else {
                code.endJump();
            }

        } else if(cur->value == "while") {
            unsigned retorno = code.getLine();
            auto cond = nd->tokens[1];
            auto cmds = nd->tokens[2];
            generateCondition(cond, scope, code);
            generateCommands(cmds, scope, code);

            // Indicar endereço do início do while
            auto dsvi = new cmd::Cmd("DSVI", {std::to_string(retorno)});
            code.saveCommand(dsvi);
            code.endJump();
        } else if(cur->type.pattern == lex::pattern::IDENTIFIER) {
            auto pusher = new cmd::Cmd("PSHR");
            code.saveCommand(pusher);
            code.initializeJump(pusher);
            auto v = nd->tokens[1]->tokens;
            std::for_each(v.rbegin(), v.rend(), [&code](ast::Node* id){
                auto param = new cmd::Cmd("PRMT", {id->value});
                code.saveCommand(param);
            });

            auto chpr = new cmd::Cmd("CHPR", {"1"});
            code.saveCommand(chpr);
            code.endJump();
        }
    }
}

/**
 * @def
 * Trata acerca da geração de código da declaração de variáveis,
 * envolvendo as instruções que indicam a presença de parâmetros
 * no topo da pilha.
 *
 * @Instruções
 * ALME: Reserva posições de memória (Indica declarção de variáveis)
 */
bool cmd::generateDeclarations(const ast::Node* node, sem::scopeController & scope, cmd::Code & code) {
    for(const auto nd : node->tokens) {
        for(const auto id : nd->tokens[1]->tokens) {
            scope.declare(id->value);
            auto alme = new cmd::Cmd("ALME", {id->value});
            code.saveCommand(alme);
        }
    }
    return true;
}

/**
 * @def
 * Trata acerca da geração de código da assinatura do método,
 * envolvendo as instruções que indicam a presença de parâmetros
 * no topo da pilha.
 *
 * @Instruções
 * DESM: Desaloca um valor do topo para argumentos de função.
 *
 * @Observações
 * Early Return Pattern - O método não possui parâmetros.
 */
bool cmd::generateSignature(const ast::Node* node, sem::scopeController & scope, cmd::Code & code) {
    if(node->tokens.size() < 3) return true;
    for(const auto nd : node->tokens[2]->tokens) {
        const auto id = nd->tokens[1];
        scope.declare(id->value);
        auto alme = new cmd::Cmd("DESM", {id->value});
        code.saveCommand(alme);
    }
    return true;
}

/**
 * @def
 * Trata acerca da geração de código do retorno do método,
 * envolvendo as instruções que indicam finalização do procedimento
 *
 * @Instruções
 * RTPR: Indica ponto de encerramento do procedimento
 */
bool cmd::generateReturn(const ast::Node* node, sem::scopeController & scope, cmd::Code & code) {
    generateExpression(node->tokens[1]->tokens[0], scope, code);
    auto rtpr = new cmd::Cmd("RTPR");
    code.saveCommand(rtpr);
    return true;
}

/**
 * @def
 * Trata acerca da geração de código do procedimento padrão (INIT),
 * envolvendo as instruções que indicam inicialização e encerramento
 * do programa, bem como inicialização do seu escopo.
 *
 * @Instruções
 *      INPP: Indica ponto de inicialização do programa
 * <br> PARA: Indica ponto de encerramento do programa
 */
void cmd::generateMain(ast::Node* node, sem::scopeController & scope, cmd::Code & code) {
    auto inpp = new cmd::Cmd("INPP");
    code.saveCommand(inpp);
    scope.initializeScope("main");
    for(auto nd : node->tokens) {
        if(nd->type.pattern == lex::pattern::DC) generateDeclarations(nd, scope, code);
        if(nd->type.pattern == lex::pattern::CMDS) generateCommands(nd, scope, code);
    }
    auto para = new cmd::Cmd("PARA");
    code.saveCommand(para);
}

/**
 * @def
 * Trata acerca da geração de código de procedimentos e envolve instruções
 * que indicam inicialização e encerramento de procedimento, bem como
 * inicialização do seu escopo.
 *
 * @Instruções
 * PROC: Indica chamada de procedimento
 */
void cmd::generateMethod(ast::Node* node, sem::scopeController & scope, cmd::Code & code) {
    scope.initializeScope(node->tokens[0]->tokens[0]->value);
    auto proc = new cmd::Cmd("PROC", {node->tokens[0]->tokens[0]->value});
    code.saveCommand(proc);
    for(const auto nd : node->tokens) {
        if(nd->type.pattern == lex::pattern::SIGNATURE) generateSignature(nd, scope, code);
        if(nd->type.pattern == lex::pattern::DC) generateDeclarations(nd, scope, code);
        if(nd->type.pattern == lex::pattern::CMDS) generateCommands(nd, scope, code);
        if(nd->type.pattern == lex::pattern::RETURN) generateReturn(nd, scope, code);
    }
}

/**
 * @def
 * Procedimento-base responsável por coordenar o início da geração
 * de código do programa. Esse procedimento trata da definição do
 * arquivo de leitura das instruções, bem como define o formato de
 * geração ao abordar primeiramente o parâmetro visando definir um
 * endereço padrão de chamada de procedimento.
 *
 * @Observações
 *      Root Size Condition - Analisa de existe declaração de método
 * <br> Signature Size Condition - Verifica se existe parâmetros
 */
bool cmd::generate(const ast::Node* root) {
    sem::scopeController scope;
    cmd::Code code("../Documentos/code/code.txt");

    if(root->tokens.size() > 2) {
        auto signature = root->tokens[2]->tokens[0];
        auto method = signature->tokens[0]->value;

        if(signature->tokens.size() > 2) scope.saveSignature(method, signature->tokens[2]->tokens.size());
        else scope.saveSignature(method);
    }

    if(root->tokens.size() == 3) generateMethod(root->tokens[2], scope, code);
    generateMain(root->tokens[1], scope, code);
    code.generateCode();
    std::cout << "Code Generation Concluded!" << std::endl;

    return true;
}
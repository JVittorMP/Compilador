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

void getExpression(ast::Node *node, sem::scopeController & scope, cmd::Code & code) {
    if(node->type == "Num") {
        auto* crct = new cmd::Cmd("CRCT", {node->value});
        code.saveCommand(crct);
        return;
    }
    if(node->type == "Identifier") {
        auto* crvl = new cmd::Cmd("CRVL", {node->value});
        code.saveCommand(crvl);
        return;
    }
    getExpression(node->tokens[1], scope, code);
    getExpression(node->tokens[0], scope, code);
    auto* opr = new cmd::Cmd(getOperatorCmd(node->value));
    code.saveCommand(opr);
}

void getCondition(ast::Node *node, sem::scopeController & scope, cmd::Code & code) {
    getExpression(node->tokens[0]->tokens[0], scope, code);
    getExpression(node->tokens[2]->tokens[0], scope, code);
    auto* comp = new cmd::Cmd(getComparisonCmd(node->tokens[1]->tokens[0]->value));
    code.saveCommand(comp);
    auto* dsvf = new cmd::Cmd("DSVF");
    code.saveCommand(dsvf);
    code.initializeJump(dsvf);
}

// → LEIT : Lê um dado de entrada para o topo da pilha
// → ELIN : Indica Inicio de ELSE
// → ELND : Indica Fim de ELSE
// → DSVX : Indica Fim de IF/WHILE
void generateCommands(ast::Node *node, sem::scopeController & scope, cmd::Code & code) {
    for(auto nd : node->tokens) {
        auto cur = nd->tokens[0];
        if(cur->value == "System.out.println") {
            getExpression(nd->tokens[1]->tokens[0], scope, code);
            auto* impr = new cmd::Cmd("IMPR");
            code.saveCommand(impr);
        } else if(cur->value == "=") {
            if(cur->tokens[1]->type == "Input") {
                auto* leit = new cmd::Cmd("LEIT");
                code.saveCommand(leit);
            } else {
                getExpression(cur->tokens[1]->tokens[0], scope, code);
            }
            auto* armz = new cmd::Cmd("ARMZ", {cur->tokens[0]->value});
            code.saveCommand(armz);
        } else if(cur->value == "if") {
            // Para aumentar os passos dos elses para cada if
            code.ifsc += nd->tokens.size() > 3;
            auto cond = nd->tokens[1];
            auto cmds = nd->tokens[2];
            getCondition(cond, scope, code);
            generateCommands(cmds, scope, code);
            //code.endJump();

            // Não tem else
            if(nd->tokens.size() > 3) {
                code.ifsc--;
                auto* dsvf = new cmd::Cmd("DSVI");
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
            getCondition(cond, scope, code);
            generateCommands(cmds, scope, code);

            // Indicar endereço do início do while
            auto* dsvi = new cmd::Cmd("DSVI", {std::to_string(retorno)});
            code.saveCommand(dsvi);
            code.endJump();
        } else if(cur->type == "Identifier") {
            auto* pusher = new cmd::Cmd("PSHR");
            code.saveCommand(pusher);
            code.initializeJump(pusher);
            auto v = nd->tokens[1]->tokens;
            std::for_each(v.rbegin(), v.rend(), [&code](ast::Node* id){
                auto* param = new cmd::Cmd("PARM", {id->value});
                code.saveCommand(param);
            });
//            for(const auto id : nd->tokens[1]->tokens) {
//                auto* param = new cmd::Cmd("PARM", {id->value});
//                code.saveCommand(param);
//            }
            auto* chpr = new cmd::Cmd("CHPR", {"1"});
            code.saveCommand(chpr);
            code.endJump();
        }
    }
}

bool generateDeclarations(const ast::Node* node, sem::scopeController & scope, cmd::Code & code) {
    for(const auto nd : node->tokens) {
        for(const auto id : nd->tokens[1]->tokens) {
            scope.declare(id->value);
            auto* alme = new cmd::Cmd("ALME", {id->value});
            code.saveCommand(alme);
        }
    }
    return true;
}

/*
 * DESM -> Desaloca um valor do topo para argumentos de função
 */
bool generateSignature(const ast::Node* node, sem::scopeController & scope, cmd::Code & code) {
    // Caso não haja parâmetros
    if(node->tokens.size() < 3) return true;
    for(const auto nd : node->tokens[2]->tokens) {
        const auto id = nd->tokens[1];
        scope.declare(id->value);
        auto* alme = new cmd::Cmd("DESM", {id->value});
        code.saveCommand(alme);
    }
    return true;
}

bool generateReturn(const ast::Node* node, sem::scopeController & scope, cmd::Code & code) {
    getExpression(node->tokens[1]->tokens[0], scope, code);
    auto* rtpr = new cmd::Cmd("RTPR");
    code.saveCommand(rtpr);
    return true;
}

void generateMain(ast::Node *node, sem::scopeController & scope, cmd::Code & code) {
    auto* inpp = new cmd::Cmd("INPP");
    code.saveCommand(inpp);
    scope.initializeScope("main");
    for(auto nd : node->tokens) {
        if(nd->type == "DC") generateDeclarations(nd, scope, code);
        if(nd->type == "CMDS") generateCommands(nd, scope, code);
    }
    auto* para = new cmd::Cmd("PARA");
    code.saveCommand(para);
}

// -> Proc, chamada de procedimento
void generateMethod(ast::Node *node, sem::scopeController & scope, cmd::Code & code) {
    scope.initializeScope(node->tokens[0]->tokens[0]->value);
    auto* proc = new cmd::Cmd("PROC", {node->tokens[0]->tokens[0]->value});
    code.saveCommand(proc);
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
    cmd::Code code("../Documentos/code/code.txt");

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


    if(root->tokens.size() == 3) generateMethod(root->tokens[2], scope, code);
    generateMain(root->tokens[1], scope, code);
    code.generateCode();

    // for(auto nd : root->tokens) {
    //     if(nd->type == "INIT") {
    //         generateMain(nd, scope, code);
    //         code.saveCommand(cmd::Cmd("PARA"));
    //     } else if(nd->type == "METODO") {
    //         generateMethod(nd, scope, code);
    //     }
    // }

    return true;
}
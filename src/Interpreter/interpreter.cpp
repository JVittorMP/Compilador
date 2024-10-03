#include "../def.h"

/**
 * @def
 * Procedimento responsável por realizar a interpretação
 * do código-objeto, associando uma série de passos a cada
 * instrução obtida.
 */
void exec::interpret(exec::Interpreter & interpreter) {
    unsigned i = interpreter.cursor;
    bool flag = true, jump = false;
    while(flag) {
        auto cmd = interpreter.cmds[i];
        switch(cmd::stringToEnum(cmd.cmd)) {
            case cmd::command::PROC:
                interpreter.scope.initializeScope(cmd.cmd);
                break;
            case cmd::command::DESM:
                interpreter.scope.declare(cmd.args[0], interpreter.popStack());
                break;
            case cmd::command::ALME:
                interpreter.scope.declare(cmd.args[0]);
                break;
            case cmd::command::CRCT:
                interpreter.dados.push(std::stod(cmd.args[0]));
                break;
            case cmd::command::ARMZ:
                interpreter.scope.updateValue(cmd.args[0], interpreter.popStack());
                break;
            case cmd::command::CRVL: {
                double val = interpreter.getStackValue(cmd.args[0]);
                interpreter.dados.push(val);
                break;
            }
            case cmd::command::CPMA: {
                const double s = interpreter.popStack();
                const double f = interpreter.popStack();
                interpreter.dados.push(f > s);
                break;
            }
            case cmd::command::CPME: {
                const double s = interpreter.popStack();
                const double f = interpreter.popStack();
                interpreter.dados.push(f < s);
                break;
            }
            case cmd::command::CPIG: {
                const double s = interpreter.popStack();
                const double f = interpreter.popStack();
                interpreter.dados.push(f == s);
                break;
            }
            case cmd::command::CDES: {
                const double s = interpreter.popStack();
                const double f = interpreter.popStack();
                interpreter.dados.push(f != s);
                break;
            }
            case cmd::command::CPMI: {
                const double s = interpreter.popStack();
                const double f = interpreter.popStack();
                interpreter.dados.push(f <= s);
                break;
            }
            case cmd::command::CMAI: {
                const double s = interpreter.popStack();
                const double f = interpreter.popStack();
                interpreter.dados.push(f >= s);
                break;
            }
            case cmd::command::DSVF:
                if(!interpreter.popStack()) {
                    i = std::stod(cmd.args[0]);
                    jump = true;
                }
                break;
            case cmd::command::DSVI:
                i = std::stod(cmd.args[0]);
                jump = true;
                break;
            case cmd::command::IMPR: {
                std::cout << interpreter.popStack() << std::endl;
                break;
            }
            case cmd::command::LEIT: {
                double x;
                std::cin >> x;
                interpreter.dados.push(x);
                break;
            }
            case cmd::command::SOMA: {
                const double s = interpreter.popStack();
                const double f = interpreter.popStack();
                interpreter.dados.push(f + s);
                break;
            }
            case cmd::command::SUBT: {
                const double s = interpreter.popStack();
                const double f = interpreter.popStack();
                interpreter.dados.push(f - s);
                break;
            }
            case cmd::command::MULT: {
                const double s = interpreter.popStack();
                const double f = interpreter.popStack();
                interpreter.dados.push(f * s);
                break;
            }
            case cmd::command::DIVI: {
                const double s = interpreter.popStack();
                const double f = interpreter.popStack();
                if(s == 0) throw compiler::Exception(compiler::Exception::model::RUNTIME, "Division by 0");
                interpreter.dados.push(f / s);
                break;
            }
            case cmd::command::INVE: {
                const double top = interpreter.popStack();
                interpreter.dados.push(-top);
                break;
            }
            case cmd::command::INPP:
                interpreter.scope.initializeScope("main");
                break;
            case cmd::command::PARA:
                flag = false;
                break;
            case cmd::command::CHPR:
                i = std::stod(cmd.args[0]);
                jump = true;
                break;
            case cmd::command::RTPR: {
                interpreter.popStack();
                interpreter.scope.endScope();
                i = interpreter.popStack();
                jump = true;
                break;
            }
            case cmd::command::PRMT:
                interpreter.dados.push(interpreter.scope.returnVarValue(cmd.args[0]));
                break;
            case cmd::command::PSHR:
                interpreter.dados.push(std::stod(cmd.args[0]));
                break;
            case cmd::command::ERRO:
                const std::string msg = std::format("Erro no Comando [{}]: {}", i, cmd.toString());
                throw compiler::Exception(compiler::Exception::model::RUNTIME, msg);
        }
        if(jump) jump = false;
        else i++;
    }
}

int main() {
    try {
        exec::Interpreter interpreter("../Documentos/code/code.txt");
        exec::interpret(interpreter);
    } catch(compiler::Exception & e) {
        std::cerr << e.what() << std::endl;
    }
}
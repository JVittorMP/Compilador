#include "../basic.h"

#include "../CodeGenerator/cmd.h"
#include "../Semantizer/sem.h"

double getStackValue(std::string val, sem::scopeController& scope) {
    bool neg = val.front() == '-';
    if(neg) val = val.substr(1, std::string::npos);
    double value = scope.returnVarValue(val);
    return neg ? - value : value;
}

double pop(std::stack<double> & st) {
    double d = st.top();
    st.pop();
    return d;
}

void interpret(std::deque<cmd::Cmd> & cmds, std::stack<double> & pDados, sem::scopeController & scope, unsigned init) {
    unsigned i = init;
    bool flag = true, jump = false;
    while(flag) {
        auto cmd = cmds[i];
        switch(cmd::stringToEnum(cmd.cmd)) {
            case cmd::command::PROC:
                scope.initializeScope(cmd.cmd);
                break;
            case cmd::command::DESM:
                // Arrumar, pois os parâmetros vem invertidos
                scope.declare(cmd.args[0], pop(pDados));
                break;
            case cmd::command::ALME:
                scope.declare(cmd.args[0]);
                break;
            case cmd::command::CRCT:
                pDados.push(std::stod(cmd.args[0]));
                break;
            case cmd::command::ARMZ:
                scope.updateValue(cmd.args[0], pop(pDados));
                break;
            case cmd::command::CRVL: {
                double val = getStackValue(cmd.args[0], scope);
                pDados.push(val);
                break;
            }
            case cmd::command::CPMA: {
                double s = pop(pDados);
                double f = pop(pDados);
                pDados.push(f > s);
                break;
            }
            case cmd::command::CPME: {
                double s = pop(pDados);
                double f = pop(pDados);
                pDados.push(f < s);
                break;
            }
            case cmd::command::CPIG: {
                double s = pop(pDados);
                double f = pop(pDados);
                pDados.push(f == s);
                break;
            }
            case cmd::command::CDES: {
                double s = pop(pDados);
                double f = pop(pDados);
                pDados.push(f != s);
                break;
            }
            case cmd::command::CPMI: {
                double s = pop(pDados);
                double f = pop(pDados);
                pDados.push(f <= s);
                break;
            }
            case cmd::command::CMAI: {
                double s = pop(pDados);
                double f = pop(pDados);
                pDados.push(f >= s);
                break;
            }
            case cmd::command::DSVF:
                if(!pop(pDados)) {
                    i = std::stod(cmd.args[0]);
                    jump = true;
                }
                break;
            case cmd::command::DSVI:
                i = std::stod(cmd.args[0]);
                jump = true;
                break;
            case cmd::command::IMPR: {
                std::cout << pop(pDados) << std::endl;
                break;
            }
            case cmd::command::LEIT: {
                double x;
                std::cin >> x;
                pDados.push(x);
                break;
            }
            case cmd::command::SOMA: {
                double s = pop(pDados);
                double f = pop(pDados);
                pDados.push(f + s);
                break;
            }
            case cmd::command::SUBT: {
                double s = pop(pDados);
                double f = pop(pDados);
                pDados.push(f - s);
                break;
            }
            case cmd::command::MULT: {
                double s = pop(pDados);
                double f = pop(pDados);
                pDados.push(f * s);
                break;
            }
            case cmd::command::DIVI: {
                double s = pop(pDados);
                double f = pop(pDados);
                pDados.push(f / s);
                break;
            }
            case cmd::command::INPP:
                scope.initializeScope("main");
                break;
            case cmd::command::PARA:
                flag = false;
                break;
            case cmd::command::CHPR:
                i = std::stod(cmd.args[0]);
                jump = true;
                break;
            case cmd::command::RTPR: {
                double ans = pop(pDados);
                scope.endScope();
                i = pop(pDados);
                jump = true;
                break;
            }
            case cmd::command::PARM:
                pDados.push(scope.returnVarValue(cmd.args[0]));
                break;
            case cmd::command::PSHR:
                pDados.push(std::stod(cmd.args[0]));
                break;
            case cmd::command::ERRO:
                std::cout << "Erro no Comando [" << i << "]: " << cmd << std::endl;
                break;
        }
        if(jump) jump = false;
        else i++;
    }
}

int main() {
    std::deque<cmd::Cmd> cmds = {cmd::Cmd("INIT")};
    std::stack<double> pDados;
    sem::scopeController scope;

    std::ifstream code("../Documentos/code/code02.txt");
    std::string line;
    unsigned init = 0, l = 1;

    if(!code) std::cout << "Error in creating file!!!" << std::endl;
    else std::cout << "Success in creating file!!!" << std::endl;

    while(getline(code, line)) {
        std::deque<std::string> args;

        line = line.substr(1, size(line) - 2);
        size_t x = 0, y = line.find_first_of(',', x);
        std::string cmd = line.substr(x, y);

        while(y != std::string::npos) {
            x = y, y = line.find_first_of(',', y + 1);
            args.push_back(line.substr(x + 2, y));
        }

        if(cmd == "INPP") init = l;
        cmds.emplace_back(cmd, args);
        l++;
    }
    interpret(cmds, pDados, scope, init);
}
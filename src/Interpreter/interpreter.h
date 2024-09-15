#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "../basic.h"
#include "../CodeGenerator/cmd.h"
#include "../Semantizer/sem.h"

namespace gen {
    class Interpreter {
    public:
        std::deque<cmd::Cmd> cmds = {cmd::Cmd("INIT")};
        std::stack<double> dados;
        sem::scopeController scope;
        unsigned cursor = 0;

        explicit Interpreter(const std::string & path) {
            std::ifstream code(path);
            std::string line;
            unsigned l = 0;

            if(!code) std::cout << "Error in creating file!!!" << std::endl;
            else std::cout << "Success in creating file!!!" << std::endl;

            while(l++, getline(code, line)) {
                std::deque<std::string> args;

                line = line.substr(1, size(line) - 2);
                size_t x = 0, y = line.find_first_of(',', x);
                std::string cmd = line.substr(x, y);

                while(y != std::string::npos) {
                    x = y, y = line.find_first_of(',', y + 1);
                    args.push_back(line.substr(x + 2, y));
                }

                if(cmd == "INPP") cursor = l;
                cmds.emplace_back(cmd, args);
            }

            code.close();
        }

        double getStackValue(std::string val) {
            const bool neg = val.front() == '-';
            if(neg) val = val.substr(1, std::string::npos);
            const double value = scope.returnVarValue(val);
            return neg ? - value : value;
        }

        double popStack() {
            const double d = dados.top();
            dados.pop();
            return d;
        }
    };
}

#endif

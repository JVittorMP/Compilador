#ifndef CMD_H
#define CMD_H
#include "../basic.h"

namespace cmd {

    class Cmd {
    public:
        std::string cmd;
        std::deque<std::string> args;

        explicit Cmd(std::string cmd): cmd(std::move(cmd)) {};
        Cmd(std::string cmd, std::deque<std::string> args): cmd(std::move(cmd)), args(std::move(args)) {}
    };

    inline std::ostream& operator<< (std::ostream& out, Cmd const& curr) {
        out << "[" << curr.cmd;
        for(const auto & arg : curr.args) {
            out << ", " << arg;
        }
        out << "]";
        return out;
    }

    class Code {
    public:
        unsigned line = 0;
        unsigned ifsc = 0;
        std::ofstream file;
        std::deque<Cmd*> cmds;

        // Mantenedor de Desvios
        std::deque<Cmd*> dsv;

        void endJump() {
            dsv.back()->args.push_back(std::to_string(line + 1 + ifsc));
            dsv.pop_back();
        }

        void initializeJump(Cmd* & cmd) {
            //if(!dsv.empty()) {
                //dsv.back()->args.push_back(std::to_string(line + 1));
            //}
            dsv.emplace_back(cmd);
        }

        explicit Code(const std::string& file_name): file(file_name) {
            if(!file) std::cout << "Error in creating file!!!";
            else std::cout << "Success in creating file!!!";
        };

        void generateCode() {
            for(const auto & cmd : cmds) writeCommand(*cmd);
            close();
        }

        void saveCommand(Cmd* & curr) {
            cmds.push_back(curr);
            line++;
        }

        void writeCommand(const Cmd & cmd) {
            file << cmd << std::endl;
            line++;
        }

        void close() {
            file.close();
        }

        unsigned getLine() const {
            return line;
        }
    };
}

#endif

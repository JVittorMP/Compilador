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
}

#endif

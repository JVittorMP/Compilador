#ifndef CMD_H
#define CMD_H

#include "../basic.h"

namespace cmd {
    enum class command {
        PROC,
        DESM,
        ALME,
        CRCT,
        ARMZ,
        CRVL,
        CPMA,
        CPME,
        CPIG,
        CDES,
        CPMI,
        CMAI,
        DSVF,
        DSVI,
        IMPR,
        LEIT,
        SOMA,
        SUBT,
        MULT,
        DIVI,
        INPP,
        PARA,
        CHPR,
        RTPR,
        PRMT,
        PSHR,
        ERRO
    };

    command stringToEnum(const std::string& s) {
        if(s == "PROC") return cmd::command::PROC;
        if(s == "DESM") return cmd::command::DESM;
        if(s == "ALME") return cmd::command::ALME;
        if(s == "CRCT") return cmd::command::CRCT;
        if(s == "ARMZ") return cmd::command::ARMZ;
        if(s == "CRVL") return cmd::command::CRVL;
        if(s == "CPMA") return cmd::command::CPMA;
        if(s == "CPME") return cmd::command::CPME;
        if(s == "CPIG") return cmd::command::CPIG;
        if(s == "CDES") return cmd::command::CDES;
        if(s == "CPMI") return cmd::command::CPMI;
        if(s == "CMAI") return cmd::command::CMAI;
        if(s == "DSVF") return cmd::command::DSVF;
        if(s == "DSVI") return cmd::command::DSVI;
        if(s == "IMPR") return cmd::command::IMPR;
        if(s == "LEIT") return cmd::command::LEIT;
        if(s == "SOMA") return cmd::command::SOMA;
        if(s == "SUBT") return cmd::command::SUBT;
        if(s == "MULT") return cmd::command::MULT;
        if(s == "DIVI") return cmd::command::DIVI;
        if(s == "INPP") return cmd::command::INPP;
        if(s == "PARA") return cmd::command::PARA;
        if(s == "CHPR") return cmd::command::CHPR;
        if(s == "RTPR") return cmd::command::RTPR;
        if(s == "PRMT") return cmd::command::PRMT;
        if(s == "PSHR") return cmd::command::PSHR;
        return command::ERRO;
    }

    class Cmd {
    public:
        std::string cmd;
        std::deque<std::string> args;

        explicit Cmd(std::string cmd): cmd(std::move(cmd)) {};
        Cmd(std::string cmd, std::deque<std::string> args): cmd(std::move(cmd)), args(std::move(args)) {}

        std::string toString() const {
            std::string out;
            out += "[" + cmd;
            for(const auto & arg : args) {
                out += ", " + arg;
            }
            out += "]";
            return out;
        }
    };

    inline std::ostream& operator<< (std::ostream& out, Cmd const& curr) {
        out << curr.toString();
        return out;
    }

    class Code {
    public:
        unsigned line = 1;
        unsigned ifsc = 0;
        std::ofstream file;
        std::deque<Cmd*> cmds;

        // Mantenedor de Desvios
        std::deque<Cmd*> dsv;

        void endJump() {
            dsv.back()->args.push_back(std::to_string(line/*ifsc*/));
            dsv.pop_back();
        }

        void initializeJump(Cmd* & cmd) {
            dsv.emplace_back(cmd);
        }

        explicit Code(const std::string & fileName): file(fileName) {
            if(!file) {
                std::string msg = std::format("Error in creating file '{}'", fileName);
                throw compiler::Exception(compiler::Exception::type::RUNTIME, msg);
            }
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

#ifndef COMPILER_H
#define COMPILER_H

#include <utility>

namespace compiler {
    enum class exception {
        LEXICAL,
        SYNTACTIC,
        SEMANTIC,
        RUNTIME
    };

    inline std::string toString(const exception except) {
        if(except == exception::LEXICAL) return "Lexical Exception - ";
        if(except == exception::SYNTACTIC) return "Syntatic Exception - ";
        if(except == exception::SEMANTIC) return "Semantic Exception - ";
        if(except == exception::RUNTIME) return "Runtime Exception - ";
        return "Unknown Exception Type - ";
    }

    class Exception final : public std::exception {
        std::string message;

    public:
        explicit Exception(const compiler::exception exception, std::string msg): message(toString(exception) + std::move(msg)) {}

        const char* what() const noexcept override {
            return message.c_str();
        }
    };
}

#endif

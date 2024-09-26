#ifndef COMPILER_H
#define COMPILER_H

#include <utility>

namespace compiler {

    class Exception final : public std::exception {
    public:
        enum class type {
            LEXICAL,
            SYNTACTIC,
            SEMANTIC,
            RUNTIME
        };

        static inline std::string toString(const type except) {
            if(except == type::LEXICAL) return "Lexical Exception";
            if(except == type::SYNTACTIC) return "Syntatic Exception";
            if(except == type::SEMANTIC) return "Semantic Exception";
            if(except == type::RUNTIME) return "Runtime Exception";
            return "Unknown Exception Type";
        }

    private:
        std::string message;

    public:
        explicit Exception(const compiler::Exception::type exception, std::string msg): message(toString(exception) + ": " + std::move(msg)) {}

        const char* what() const noexcept override {
            return message.c_str();
        }
    };
}

#endif

#ifndef COMPILER_H
#define COMPILER_H

#include <utility>

namespace compiler {

    class Exception final : public std::exception {
    public:
        enum class model {
            LEXICAL,
            SYNTACTIC,
            SEMANTIC,
            RUNTIME
        };

        static inline std::string toString(const model except) {
            if(except == model::LEXICAL) return "Lexical Exception";
            if(except == model::SYNTACTIC) return "Syntatic Exception";
            if(except == model::SEMANTIC) return "Semantic Exception";
            if(except == model::RUNTIME) return "Runtime Exception";
            return "Unknown Exception Type";
        }

    private:
        std::string message;

    public:
        explicit Exception(const compiler::Exception::model exception, std::string msg): message(toString(exception) + ": " + std::move(msg)) {}

        const char* what() const noexcept override {
            return message.c_str();
        }
    };
}

#endif

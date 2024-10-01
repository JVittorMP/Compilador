#ifndef COMPILADORES_SEM_H
#define COMPILADORES_SEM_H

#include <utility>

#include "../basic.h"

namespace sem {

    class scope {
    public:
        std::string procedimento;
        std::deque<std::unordered_map<std::string, double>> variaveis;

        explicit scope(std::string proc): procedimento(std::move(proc)) {
            variaveis.emplace_back();
        }

        // Trocar por ranges::any_of
        bool isValid(std::string id) const {
            if(id[0] == '-') id.erase(0, 1);
            for(const auto & var : variaveis) {
                if(var.contains(id)) return true;
            }
            return false;
        }

        // Não precisa de declaração de variáveis devido às características de map
        // desde que haja atribuição de valor em algum momento do código
        bool updateValue(std::string & id, const double val) {
            // if(!escopos.back().second.contains(id)) // Throw something
            /* if(id[0] == '-') id.erase(0, 1); -> Talvez não seja necessário*/
            for(auto & var : variaveis) {
                if(var.contains(id)) {
                    var[id] = val;
                    return true;
                }
            }
            throw compiler::Exception(compiler::Exception::type::SEMANTIC, std::format("Variavel [{}] Desconhecida!", id));
        }

        double returnVarValue(const std::string & id) {
            for(auto & var : variaveis) {
                if(var.contains(id)) return var[id];
            }
            return 0;
        }

        bool declare(const std::string & id, const double val = 0) {
            for(auto & var : variaveis) {
                if(var.contains(id)) return false;
            }
            variaveis.back()[id] = val;
            return true;
        }

        void initializeScope() {
            variaveis.emplace_back();
        }

        void endScope() {
            variaveis.pop_back();
        }
    };

    class scopeController {
    public:
        std::vector<scope> escopos;
        std::unordered_map<std::string, unsigned> signatures;

        unsigned getMethodParamsSize(const std::string& s) {
            return signatures[s];
        }

        void saveSignature(const std::string& s, unsigned qtd = 0) {
            signatures[s] = qtd;
        }

        bool isValidMethod(const std::string& id) const {
            return signatures.contains(id);
        }

        bool isValid(std::string id) const {
            return escopos.back().isValid(std::move(id));
        }

        // Não precisa de declaração de variáveis devido às características de map
        // desde que haja atribuição de valor em algum momento do código
        void updateValue(std::string & id, const double val) {
            // if(!escopos.back().second.contains(id)) // Throw something
            escopos.back().updateValue(id, val);
        }

        double returnVarValue(const std::string & id) {
            return escopos.back().returnVarValue(id);
        }

        bool declare(const std::string & id, const double val = 0) {
            return escopos.back().declare(id, val);
        }

        void initializeScope(const std::string & s) {
            escopos.emplace_back(s);
        }

        void endScope() {
            escopos.pop_back();
        }

        void initializeInternScope() {
            escopos.back().initializeScope();
        }

        void endInternScope() {
            escopos.back().endScope();
        }
    };
}

#endif

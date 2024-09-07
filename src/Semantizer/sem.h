#ifndef COMPILADORES_SEM_H
#define COMPILADORES_SEM_H

#include "../basic.h"
#include "../Parser/AST/ast.h"

namespace sem {

    class scopeController {
        public:
        std::vector<std::pair<std::string, std::unordered_map<std::string, double>>> escopos;
        std::unordered_map<std::string, unsigned> signatures;

//        std::unordered_map<std::string, double> & operator [](const std::string & x) {
//            auto & mp = escopos.back().second;
//            if(mp.find(x) != mp.end()) mp[x];
//            return escopos.back().second;
//        }
//
//        scopeController& operator=(double val) {
//            this->escopos.back().second = val;
//        }

        unsigned getMethodParamsSize(const std::string& s) {
            return signatures[s];
        }

        void saveSignature(const std::string& s, unsigned qtd) {
            signatures[s] = qtd;
        }

        bool isValidMethod(const std::string& id) {
            return signatures.find(id) != signatures.end();
        }

        bool isValid(std::string id) {
            if(id[0] == '-') id.erase(0, 1);
            auto & mp = escopos.back().second;
            return mp.find(id) != mp.end();
        }

        void updateValue(const std::string & id, double val) {
            escopos.back().second[id] = val;
        }

        bool declare(const std::string & id, double val = 0) {
            auto & mp = escopos.back().second;
            if(mp.find(id) != mp.end()) return false;
            escopos.back().second[id] = val;
            return true;
        }

        void initializeScope(const std::string& s) {
            escopos.emplace_back(s, std::unordered_map<std::string, double>());
        }

        void EndScope() {
            escopos.pop_back();
        }
    };
}

#endif

#ifndef COMPILADORES_SEM_H
#define COMPILADORES_SEM_H

#include "../basic.h"

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

        void saveSignature(const std::string& s, unsigned qtd = 0) {
            signatures[s] = qtd;
        }

        bool isValidMethod(const std::string& id) const {
            return signatures.contains(id);
        }

        bool isValid(std::string id) const {
            if(id[0] == '-') id.erase(0, 1);
            auto & mp = escopos.back().second;
            return mp.contains(id);
        }

        void updateValue(const std::string & id, const double val) {
            escopos.back().second[id] = val;
        }

        bool declare(const std::string & id, const double val = 0) {
            auto & mp = escopos.back().second;
            if(mp.contains(id)) return false;
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

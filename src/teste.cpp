#include "lexer/lexer.cpp"
#include <fstream>

void iteratorTest() {
    std::vector<int> v{1,2,3,4,5};
    auto it = v.begin();
    std::cout << "it[4]: " << it[4] << std::endl;
    while(it != v.end()) {
        std::cout << (*it) << " ";
        it++;
    }
}

void tokenTest() {
    lex::token _lexema("teste", "teste", 0);
    lex::token lexema_{"teste", "teste", 0};

    std::cout << "lexema: (" << _lexema.type << ", " << _lexema.value << ", " << _lexema.linha << ")" << std::endl;
    std::cout << "lexema: (" << lexema_.type << ", " << lexema_.value << ", " << lexema_.linha <<  ")" << std::endl;

    if(_lexema == lexema_) std::cout << "iguais" << std::endl;
    else std::cout << "diferentes" << std::endl;
}

using namespace std;

int main() {
    // tokenTest();
    // iteratorTest();

    return 0;
}
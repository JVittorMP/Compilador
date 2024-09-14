#include "../src/lexer/lexer.cpp"
#include <fstream>

void iteratorTest() {
    std::vector<int> v{1,2,3,4,5};
    auto it = v.begin();
    std::cout << "it[4]: " << it[4] << std::endl;
    while(it != v.end()) {
        std::cout << (*it) << " ";
        ++it;
    }
}

void tokenTest() {
    lex::token _lexema(lex::Type{"teste"}, "teste", 0);
    lex::token lexema_{lex::Type{"teste"}, "teste", 0};

    std::cout << "lexema: (" << _lexema.type.asString() << ", " << _lexema.value << ", " << _lexema.linha << ")" << std::endl;
    std::cout << "lexema: (" << lexema_.type.asString() << ", " << lexema_.value << ", " << lexema_.linha <<  ")" << std::endl;

    if(_lexema == lexema_) std::cout << "iguais" << std::endl;
    else std::cout << "diferentes" << std::endl;
}

using namespace std;

int main() {
    std::cout << "+++ Selecione o Teste +++" << std::endl;
    std::cout << "TokenTest     - 1" << std::endl;
    std::cout << "IteratorTest  - 2" << std::endl;

    int i = 0;
    std::cin >> i;

    switch(i) {
        case 1:
            tokenTest();
            break;
        case 2:
            iteratorTest();
            break;
        default:
            break;
    }

    return 0;
}
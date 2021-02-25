#include <string>

#include "lexer.cpp"
#include "parser.cpp"

int main(void) {
    std::string program;
    Lexer *lexer;

    while (std::getline(std::cin, program)) {
        if (std::cin.eof()) break;
        lexer = new Lexer(program);
        std::cout << lexer->toString() << std::endl;
        delete lexer;
    }
    return 0;
}

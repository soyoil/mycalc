#include <string>

#include "parser.cpp"

int main(void) {
    std::string program;
    Lexer *lexer;
    Node *tree;

    while (std::getline(std::cin, program)) {
        if (std::cin.eof()) break;
        lexer = new Lexer(program);
        std::cout << lexer->toString() << std::endl;
        tree = Parser::parse(lexer->getQueue());
        std::cout << tree->toString() << std::endl;
        delete tree;
        delete lexer;
    }
    return 0;
}
